import 'package:trivia/Pages/HomePage.dart';
import 'package:trivia/Pages/leaderBoardPage.dart';
import 'package:trivia/SocketService.dart';
import 'package:flutter/material.dart';
import 'package:trivia/Pages/loginPage.dart';
import 'package:trivia/message.dart';
import 'package:trivia/history.dart';
import 'package:trivia/statistics.dart';
import 'package:trivia/Pages/roomPage.dart';
import 'package:trivia/components/erroToast.dart';
import 'dart:convert';

class UserPage extends StatefulWidget {
  final SocketService socketService;

  const UserPage({super.key, required this.socketService});

  @override
  _UserPage createState() => _UserPage(socketService);
}

class _UserPage extends State<UserPage> {
  final SocketService _socketService;
  late List<History> _history = [];
  late List<Statistic> _statistics = [];
  bool _isFloatingScreenOpen = false;
  String _enteredValue = '';

  _UserPage(this._socketService)
  {
    getInfo();
  }

  void getInfo() async{
    _socketService.sendMessage(Message(9, {}));
    Message receivedMessage = await _socketService.receiveMessage();
    if (receivedMessage.getCode() == 8) {
      Map<String, dynamic> statisticsMap = receivedMessage.getData()["statistics"];
      statisticsMap.forEach((key, value) {
        _statistics.add(Statistic(key, value));
      });
    }

    _socketService.sendMessage(Message(10, {}));
    receivedMessage = await _socketService.receiveMessage();
    if (receivedMessage.getCode() == 9) {
      List<dynamic> dynamicList =
          jsonDecode(receivedMessage.getData()["History"]);
      List<Map<String, dynamic>> historyList =
          dynamicList.cast<Map<String, dynamic>>().toList();
      for (var element in historyList) {
        _history.add(History(
            element["CategoryName"],
            element["CategoryId"],
            element["UserRank"],
            element["CorrectAnswers"],
            element["TotalAnswers"],
            element["AvergeTime"],
            element["CreationDate"]));
      }
    }
    setState(() {});
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
            backgroundColor: Colors.transparent,
            elevation: 0,
            actions: <Widget>[
              Padding(
                padding: const EdgeInsets.only(right: 20.0),
                child: IconButton(
                    icon: const Icon(
                      Icons.logout,
                      color: Colors.black,
                      size: 26.0,
                    ),
                    onPressed: () async {
                      _socketService.sendMessage(Message(3, {}));
                      final Message response =
                          await _socketService.receiveMessage();
                      if (response.getCode() == 2) {
                        Navigator.pushReplacement(
                            context,
                            MaterialPageRoute(
                                builder: (_) => LoginPage(
                                      socketService: widget.socketService,
                                    )));
                      }
                    }),
              ),
            ]),
        body: Stack(children: [
          SingleChildScrollView(
            scrollDirection: Axis.vertical,
            child: Center(
              child: Column(
                children: [
                  Padding(
                    padding: const EdgeInsets.symmetric(
                        horizontal: 16, vertical: 16),
                    child: Column(
                      children: [
                        const Text(
                          'STATS',
                          style: TextStyle(
                              fontSize: 20, fontWeight: FontWeight.bold),
                        ),
                        const SizedBox(height: 16),
                        Container(
                          decoration: BoxDecoration(
                            borderRadius: BorderRadius.circular(20),
                            border: Border.all(
                              color: Colors.black,
                              width: 5,
                            ),
                            gradient: LinearGradient(
                              colors: [
                                Colors.blue.shade200,
                                Colors.green.shade50,
                                Colors.cyan.shade300
                              ],
                            ),
                          ),
                          height: MediaQuery.of(context).size.height * 0.4,
                          width: MediaQuery.of(context).size.width * 0.5,
                          child: SingleChildScrollView(
                            scrollDirection: Axis.vertical,
                            child: DefaultTextStyle(
                              style: const TextStyle(color: Colors.black),
                              child: SingleChildScrollView(
                                scrollDirection: Axis.horizontal,
                                child: DataTable(
                                  horizontalMargin: MediaQuery.of(context).size.width * 0.125,
                                  dataTextStyle:
                                      const TextStyle(color: Colors.black),
                                  columns: const [
                                    DataColumn(
                                      label: Text('Statistics Name'),
                                    ),
                                    DataColumn(
                                      label: Text('User Results'),
                                      numeric: true,
                                    )
                                  ],
                                  rows: List.generate(_statistics.length,
                                      (index) {
                                    final statistics = _statistics[index];
                                    return DataRow(
                                      selected: true,
                                      cells: [
                                        DataCell(Text(statistics.getStatisticsName())
                                        
                                            ),
                                        DataCell(Text(
                                            statistics.getScore().toString()))
                                      ],
                                    );
                                  }),
                                ),
                              ),
                            ),
                          ),
                        ),
                      ],
                    ),
                  ),
                  const SizedBox(height: 16),
                  Padding(
                    padding: const EdgeInsets.symmetric(horizontal: 16),
                    child: Column(
                      children: [
                        const Text(
                          'HISTORY',
                          style: TextStyle(
                              fontSize: 20, fontWeight: FontWeight.bold),
                        ),
                        const SizedBox(height: 16),
                        Container(
                          decoration: BoxDecoration(
                            borderRadius: BorderRadius.circular(20),
                            border: Border.all(
                              color: Colors.black,
                              width: 5,
                            ),
                            gradient: LinearGradient(
                              colors: [
                                Colors.blue.shade200,
                                Colors.green.shade50,
                                Colors.cyan.shade300
                              ],
                            ),
                          ),
                          height: MediaQuery.of(context).size.height * 0.4,
                          width: MediaQuery.of(context).size.width * 0.7,
                          child: SingleChildScrollView(
                            scrollDirection: Axis.vertical,
                            child: DefaultTextStyle(
                              style: const TextStyle(color: Colors.black),
                              child: SingleChildScrollView(
                                scrollDirection: Axis.horizontal,
                                child: DataTable(
                                  dataTextStyle:
                                      const TextStyle(color: Colors.black),
                                  columns: const [
                                    DataColumn(
                                      label: Text('Num'),
                                      numeric: true,
                                    ),
                                    DataColumn(
                                      label: Text('Category Name'),
                                    ),
                                    DataColumn(
                                      label: Text('Category Id'),
                                      numeric: true,
                                    ),
                                    DataColumn(
                                      label: Text('User Rank'),
                                      numeric: true,
                                    ),
                                    DataColumn(
                                      label: Text('Num Answers'),
                                      numeric: true,
                                    ),
                                    DataColumn(
                                      label: Text('Num Of Correct Answers'),
                                      numeric: true,
                                    ),
                                    DataColumn(
                                      label: Text('Average Time'),
                                      numeric: true,
                                    ),
                                    DataColumn(
                                      label: Text('Creation Date'),
                                    ),
                                  ],
                                  rows: List.generate(_history.length, (index) {
                                    final history = _history[index];
                                    return DataRow(
                                      cells: [
                                        DataCell(Text((index + 1).toString())),
                                        DataCell(
                                            Text(history.getCategoryName())),
                                        DataCell(Text(history
                                            .getCategoryId()
                                            .toString())),
                                        DataCell(Text(
                                            history.getUserRank().toString())),
                                        DataCell(Text(history
                                            .getTotalAnswers()
                                            .toString())),
                                        DataCell(Text(history
                                            .getCorrectAnswers()
                                            .toString())),
                                        DataCell(Text(history
                                            .getAverageTime()
                                            .toString())),
                                        DataCell(Text(history
                                            .getCreationDate()
                                            .toString())),
                                      ],
                                    );
                                  }),
                                ),
                              ),
                            ),
                          ),
                        ),
                      ],
                    ),
                  ),
                ],
              ),
            ),
          ),
          if (_isFloatingScreenOpen) _buildFloatingScreen(),
        ]),
        backgroundColor: Colors.white,
        bottomNavigationBar: BottomNavigationBar(
            type: BottomNavigationBarType.fixed,
            items: [
              const BottomNavigationBarItem(
                  icon: Icon(
                    Icons.person,
                    color: Colors.blue,
                  ),
                  label: ''),
              const BottomNavigationBarItem(
                  icon: Icon(Icons.add_box), label: ''),
              const BottomNavigationBarItem(
                  icon: Icon(Icons.leaderboard_rounded), label: ''),
              BottomNavigationBarItem(
                  icon: Icon(Icons.home, color: Colors.grey[600]), label: ''),
            ],
            onTap: (value) {
              if (value == 1) {
                _openPopUp();
                if (_enteredValue != '') {
                  joinRoom();
                }
              }
              if (value == 2) {
                Navigator.pushReplacement(
                    context,
                    MaterialPageRoute(
                      builder: (_) => LeaderBoardPage(
                        socketService: widget.socketService,
                      ),
                    ));
              }
              if (value == 3) {
                Navigator.pushReplacement(
                  context,
                  MaterialPageRoute(
                    builder: (_) => HomePage(
                      socketService: widget.socketService,
                    ),
                  ),
                );
              }
            }),
      ),
    );
  }

  void _openPopUp() {
    setState(() {
      _isFloatingScreenOpen = true;
    });
  }

  Widget _buildFloatingScreen() {
    return Stack(
      fit: StackFit.expand,
      children: [
        Positioned.fill(
          child: GestureDetector(
            onTap: () {
              setState(() {
                _isFloatingScreenOpen = false;
              });
            },
            child: Container(color: Colors.transparent),
          ),
        ),
        Align(
          alignment: Alignment.bottomCenter,
          child: Container(
            height: 60,
            color: Colors.grey[200],
            child: Row(
              mainAxisAlignment: MainAxisAlignment.spaceEvenly,
              children: [
                InkWell(
                  onTap: () {
                    showDialog(
                      context: context,
                      builder: (BuildContext context) {
                        return AlertDialog(
                          title: const Text('Join Room'),
                          content: Column(
                            mainAxisSize: MainAxisSize.min,
                            children: [
                              TextField(
                                onChanged: (value) {
                                  _enteredValue = value;
                                },
                                keyboardType: TextInputType.number,
                                decoration: const InputDecoration(
                                  hintText: 'Enter Room ID',
                                ),
                              ),
                              const SizedBox(height: 10),
                              ElevatedButton(
                                child: const Text('Join'),
                                onPressed: () {
                                  Navigator.of(context).pop();
                                },
                              ),
                            ],
                          ),
                        );
                      },
                    );
                    setState(() {
                      _isFloatingScreenOpen = false;
                    });
                  },
                  child: const Icon(Icons.people),
                ),
                InkWell(
                  onTap: () {
                    // Handle Create icon press
                    setState(() {
                      _isFloatingScreenOpen = false;
                    });
                  },
                  child: const Icon(Icons.create),
                ),
              ],
            ),
          ),
        ),
      ],
    );
  }

  void joinRoom() async {
    _socketService.sendMessage(Message(11, {"roomId": _enteredValue}));
    final Message response = await _socketService.receiveMessage();
    if (response.getCode() == 10) {
      Navigator.pushReplacement(
        context,
        MaterialPageRoute(
          builder: (_) => RoomPage(
            socketService: widget.socketService,
            admin: false,
            roomId: int.parse(_enteredValue),
          ),
        ),
      );
    } else {
      errorToast(context, response.getData()["Error"], 2);
    }
  }
}
