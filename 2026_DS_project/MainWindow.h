#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QMessageBox>
#include <QVector>
#include <QString>
#include <QMap>
#include <QSet>

// 1. 공항 항로 네트워크 그래프 자료구조 클래스
class AirportGraph {
public:
    struct Flight {
        int toAirport;
        QString duration; // 운항 시간
        int price;        // 항공권 요금 (원)
    };

    QVector<QString> airportNames;
    QMap<int, QVector<Flight>> adjList;

    AirportGraph() {
        // 주요 거점 공항 노드 데이터 등록
        airportNames.append("김포국제공항 (GMP)"); // Index 0
        airportNames.append("제주국제공항 (CJU)"); // Index 1
        airportNames.append("김해국제공항 (PUS)"); // Index 2
        airportNames.append("대구국제공항 (TAE)"); // Index 3
        airportNames.append("광주공항 (KWJ)");     // Index 4
        airportNames.append("인천국제공항 (ICN)"); // Index 5

        // [기존 노선] 간선 정보 등록 (항공 노선 가중치 매핑)
        addFlight(0, 1, "1시간 05분", 65000);  // 김포 <-> 제주
        addFlight(0, 2, "1시간 00분", 58000);  // 김포 <-> 김해
        addFlight(0, 3, "0시간 55분", 52000);  // 김포 <-> 대구
        addFlight(0, 4, "0시간 50분", 48000);  // 김포 <-> 광주
        
        addFlight(2, 1, "0시간 50분", 45000);  // 김해 <-> 제주
        addFlight(3, 1, "0시간 55분", 49000);  // 대구 <-> 제주
        addFlight(4, 1, "0시간 45분", 42000);  // 광주 <-> 제주

        addFlight(5, 1, "1시간 10분", 72000);  // 인천 <-> 제주
        addFlight(5, 2, "1시간 05분", 64000);  // 인천 <-> 김해
    }

    void addFlight(int u, int v, QString dur, int p) {
        adjList[u].append({v, dur, p});
        adjList[v].append({u, dur, p}); 
    }

    QVector<Flight> getDirectFlights(int airportIndex) {
        if (adjList.contains(airportIndex)) {
            return adjList[airportIndex];
        }
        return QVector<Flight>();
    }
};

// 2. 대화면 시각화 GUI 및 실시간 예매 메인 윈도우 클래스
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("전국 주요 공항 항공편 실시간 지도 조회 및 예매 시스템");
        
        // 2분할 대화면창 레이아웃 크기 지정
        resize(950, 600);

        graph = new AirportGraph();
        currentDepartureIndex = -1; // 초기화 (선택 전)

        QWidget* centralWidget = new QWidget(this);
        setCentralWidget(centralWidget);
        
        // 메인 레이아웃: 좌측(세로 지도)과 우측(결과 정보창) 분할 배치
        QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
        mainLayout->setSpacing(15);
        mainLayout->setContentsMargins(15, 15, 15, 15);

        // --- 1. 좌측 패널: map.png 이미지 레이블 존 ---
        imageLabel = new QLabel(this);
        imageLabel->setFixedSize(480, 520); 
        imageLabel->setStyleSheet("background-color: #eceff1; border: 1px solid #b0bec5; border-radius: 6px;");
        
        QPixmap pixmap("map.png"); 
        if (!pixmap.isNull()) {
            imageLabel->setPixmap(pixmap.scaled(480, 520, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        } else {
            imageLabel->setText("<div style='padding-top:240px; text-align:center; color:#78909c; font-size:13px;'>"
                                "<b>[ map.png 로드 실패 ]</b><br>탐색기에 세로형 대한민국 지도를 업로드해 주세요.</div>");
        }
        imageLabel->setAlignment(Qt::AlignCenter);
        mainLayout->addWidget(imageLabel);

        // [버튼 좌표 구조] 세로 지도 기반 고정 위치
        setupAirportButton(5, "인천공항", 40, 110);  
        setupAirportButton(0, "김포공항", 150, 90);  
        setupAirportButton(3, "대구공항", 250, 235); 
        setupAirportButton(4, "광주공항", 100, 310); 
        setupAirportButton(2, "김해공항", 300, 320); 
        setupAirportButton(1, "제주공항", 90, 450); 


        // --- 2. 우측 패널: 결과 데이터 렌더링 및 인터랙티브 예매 보드 ---
        QWidget* rightPanel = new QWidget(this);
        QVBoxLayout* rightLayout = new QVBoxLayout(rightPanel);
        rightLayout->setContentsMargins(0, 0, 0, 0);

        QLabel* sideTitle = new QLabel("<h2 style='color:#0d47a1; margin:0px 0px 5px 0px;'>✈️ 항공 스케줄 및 실시간 예매</h2>", this);
        rightLayout->addWidget(sideTitle);

        infoLabel = new QLabel(this);
        resetInfoLabel(); // 초기 가이드 문구 로드
        infoLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
        infoLabel->setWordWrap(true);
        infoLabel->setStyleSheet("background-color: #fafafa; border: 1px solid #cfd8dc; padding: 20px; border-radius: 6px;");
        
        // HTML 테이블 내부 앵커 텍스트(<a href>) 클릭을 감지하는 시그널 연결
        infoLabel->setOpenExternalLinks(false); // 웹브라우저 차단
        connect(infoLabel, &QLabel::linkActivated, this, &MainWindow::handleBookingSlot);

        rightLayout->addWidget(infoLabel);
        mainLayout->addWidget(rightPanel, 1);
    }

    ~MainWindow() {
        delete graph;
    }

private:
    AirportGraph* graph;
    QLabel* imageLabel;
    QLabel* infoLabel;
    int currentDepartureIndex; // 현재 활성화된 출발 공항 인덱스 기록용

    void resetInfoLabel() {
        infoLabel->setText("<h3 style='color:#1565c0; margin-top:10px;'> 실시간 공항 노선 안내</h3>"
                           "<p style='font-size:13px; color:#555; line-height:140%;'>"
                           "왼쪽 지도에서 조회를 원하는 <b>공항 버튼을 클릭</b>해 주세요.<br><br>"
                           "클릭 시 해당 공항을 기준으로 연결된 하늘길의 소요 시간 및 운임 요금을 계산합니다.<br>"
                           "조회 후 리스트에서 <u>[예매하기] 링크</u>를 누르시면 예매가 진행됩니다.</p>");
    }

    void setupAirportButton(int index, QString name, int x, int y) {
        QPushButton* btn = new QPushButton(name, imageLabel);
        btn->setGeometry(x, y, 105, 32); 
        
        btn->setStyleSheet(
            "QPushButton {"
            "   background-color: rgba(255, 255, 255, 230);"
            "   border: 2px solid #0d47a1;"
            "   border-radius: 6px;"
            "   font-weight: bold;"
            "   color: #0d47a1;"
            "   font-size: 12px;"
            "}"
            "QPushButton:hover {"
            "   background-color: #0d47a1;"
            "   color: white;"
            "}"
        );

        connect(btn, &QPushButton::clicked, this, [this, index]() {
            loadFlightSchedule(index);
        });
    }

    // 공항 조회 화면 렌더링
    void loadFlightSchedule(int startAirportIndex) {
        currentDepartureIndex = startAirportIndex; // 상태 저장
        QString currentAirport = graph->airportNames[startAirportIndex];
        QVector<AirportGraph::Flight> flights = graph->getDirectFlights(startAirportIndex);

        QString uiText = QString("<h3 style='color:#0288d1; margin: 0px 0px 10px 0px;'> %1 출발 노선 분석</h3>").arg(currentAirport);
        uiText += "<p style='color:#616161; font-size:12px; margin-bottom:15px;'>※ 예매를 원하시면 우측 예매처의 링크를 클릭하세요.</p>";
        
        if (flights.isEmpty()) {
            uiText += "<p style='color:#d32f2f; font-weight:bold;'>현재 정기 편성 노선이 존재하지 않습니다.</p>";
        } else {
            uiText += "<table border='0' cellspacing='3' cellpadding='8' width='100%' style='font-size:13px;'>";
            uiText += "<tr style='background-color:#b3e5fc; font-weight:bold; color:#01579b; text-align:center;'>"
                      "<td>도착 공항 노드</td><td>비행 시간</td><td>편도 요금</td><td>예매 서비스</td></tr>";

            for (int i = 0; i < flights.size(); ++i) {
                QString destName = graph->airportNames[flights[i].toAirport];
                QString duration = flights[i].duration;
                QString priceStr = QString("%1 원").arg(flights[i].price);

                // <a href="도착지인덱스"> 구조를 통해 클릭된 행의 타겟 데이터를 슬롯으로 전달
                uiText += QString("<tr style='background-color:#ffffff; border-bottom:1px solid #e0e0e0; text-align:center;'>"
                                  "<td style='color:#2e7d32; font-weight:bold; text-align:left;'>➡️ %1</td>"
                                  "<td> %2</td>"
                                  "<td style='color:#c62828; font-weight:bold;'>%3</td>"
                                  "<td><a href='%4' style='color:#1565c0; font-weight:bold; text-decoration:none;'>[예매하기]</a></td>"
                                  "</tr>").arg(destName, duration, priceStr, QString::number(flights[i].toAirport));
            }
            uiText += "</table>";
        }

        infoLabel->setText(uiText);
        QMessageBox::information(this, "실시간 조회 완료", QString("%1 항공편 정보 로드 성공!").arg(currentAirport));
    }

    //   예매하기 클릭 및 최종 확인/취소 트랜잭션 처리
    void handleBookingSlot(const QString &link) {
        if (currentDepartureIndex == -1) return;

        int destAirportIndex = link.toInt();
        QString departure = graph->airportNames[currentDepartureIndex];
        QString destination = graph->airportNames[destAirportIndex];

        // 1. 해당 노선의 세부 가중치(금액, 시간) 추출
        QVector<AirportGraph::Flight> flights = graph->getDirectFlights(currentDepartureIndex);
        QString duration = "";
        int price = 0;
        for (const auto& flight : flights) {
            if (flight.toAirport == destAirportIndex) {
                duration = flight.duration;
                price = flight.price;
                break;
            }
        }

        // 2. 예매 의사를 묻는 질문 팝업 모달창 띄우기
        QString questionText = QString("=== 항공권 예매 확인 ===\n\n"
                                       "• 출발지: %1\n"
                                       "• 도착지: %2\n"
                                       "• 소요시간: %3\n"
                                       "• 결제요금: %4 원\n\n"
                                       "항공권을 예매하시겠습니까?")
                                       .arg(departure, destination, duration, QString::number(price));

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "항공권 결제 승인 요청", questionText,
                                      QMessageBox::Yes | QMessageBox::No);

        // 3. 사용자가 [확인(Yes)]을 누르면 영수증 출력 및 가이드 창 갱신
        if (reply == QMessageBox::Yes) {
            QMessageBox::information(this, "예매 완료", QString(" 성공적으로 %1행 항공권 결제가 완료되었습니다!").arg(destination));

            // 우측 디스플레이 보드를 '최종 발권 명세서(영수증)' 스타일로 리렌더링
            QString successTemplate = QString(
                "<div style='background-color:#e8f5e9; border:2px solid #2e7d32; padding:15px; border-radius:6px;'>"
                "<h3 style='color:#1b5e20; margin:0px;'> 전자 항공권 발권 명세서</h3><hr>"
                "<p style='font-size:14px; color:#333; line-height:160%;'>"
                "<b>■ 상태:</b> <span style='color:#2e7d32; font-weight:bold;'>예매가 확정되었습니다.</span><br>"
                "<b>■ 탑승 구간:</b> %1 -> %2<br>"
                "<b>■ 비행 정보:</b> 직항선로 (%3 소요)<br>"
                "<b>■ 결제 금액:</b> <span style='color:#c62828; font-weight:bold;'>%4 원</span> (기본 운임)</p>"
                "<hr><p style='font-size:12px; color:#666;'>※ 다른 항공편 조회를 원하시면 지도의 공항 버튼을 다시 클릭하세요.</p>"
                "</div>"
            ).arg(departure, destination, duration, QString::number(price));

            infoLabel->setText(successTemplate);
        } else {
            // 사용자가 [취소(No)]를 선택한 경우
            QMessageBox::warning(this, "예매 취소", "항공권 결제 및 예매 요청이 취소되었습니다.");
        }
    }
};

#endif // MAINWINDOW_H