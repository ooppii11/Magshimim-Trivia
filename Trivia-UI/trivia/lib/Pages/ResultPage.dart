import 'package:flutter/material.dart';
import 'package:trivia/SocketService.dart';
import 'package:trivia/UserResult.dart';
import 'package:trivia/Pages/HomePage.dart';
import 'package:trivia/message.dart';
import 'dart:convert';

class ResultPage extends StatefulWidget {
  final SocketService socketService;
  const ResultPage({
    super.key,
    required this.socketService,
  });
  @override
  _ResultPageState createState() => _ResultPageState(socketService);
}

class _ResultPageState extends State<ResultPage> {
  final SocketService _socketService;
  List<UserResult> _results = [];

  _ResultPageState(this._socketService) {
    getGameResults();
  }

  getGameResults() async{
    _socketService.sendMessage(Message(24, {}));
    Message resivedMessage = await _socketService.receiveMessage();
    if(resivedMessage.getCode() == 23) {
      List<dynamic> dynamicList = jsonDecode(resivedMessage.getData()["Results"]);
      List<Map<String, dynamic>> historyList = dynamicList.cast<Map<String, dynamic>>().toList();
      for (var element in historyList) {
        _results.add(UserResult(element["Username"], element["CorrectAnswerCount"], element["WrongAnswerCount"], element["AverageAnswerTime"]));
      }
      _results.sort((a, b) {
        int compareField1 =
            b.getCorrectAnswersCount().compareTo(a.getCorrectAnswersCount());
        if (compareField1 != 0) {
          return compareField1;
        }
        return a.getAverageAnswerTime().compareTo(b.getAverageAnswerTime());
      });
      setState(() {
        _results;
      });
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Container(
        color: Colors.lightBlue,
        child: Column(
          children: [
            Container(
              height: MediaQuery.of(context).size.height * 0.15,
              width: MediaQuery.of(context).size.width,
              color: Color.fromARGB(255, 111, 156, 235),
              padding: const EdgeInsets.all(16.0),
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  Align(
                    alignment: Alignment.center,
                    child: const SizedBox(height: 8.0),
                  ),
                  Align(
                    alignment: Alignment.center,
                    child: Text(
                      "Game results:",
                      style: const TextStyle(
                        fontSize: 28,
                        fontWeight: FontWeight.bold,
                        color: Colors.black,
                      ),
                    ),
                  ),
                ],
              ),
            ),
            Expanded(
              child: Container(
                width: MediaQuery.of(context).size.width,
                color: Color.fromARGB(255, 29, 45, 68),
                padding: const EdgeInsets.all(16.0),
                child: Center(
                  child: Container(
                    width: MediaQuery.of(context).size.width * 0.7,
                    //constraints: BoxConstraints(maxWidth: MediaQuery.of(context).size.width * 0.7, maxHeight: MediaQuery.of(context).size.height * 0.7, minWidth: MediaQuery.of(context).size.width * 0.7, minHeight: MediaQuery.of(context).size.height * 0.7),
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
                    child: SingleChildScrollView(
                      scrollDirection: Axis.vertical,
                      child: SingleChildScrollView(
                        scrollDirection: Axis.horizontal,
                        child: Center(
                          child: DataTable(
                            //horizontalMargin: MediaQuery.of(context).size.width * 0.175,
                            dataTextStyle: const TextStyle(color: Colors.black),
                            columns: const [
                              DataColumn(
                                label: Text(
                                  'Place',
                                  style: const TextStyle(
                                    fontSize: 20,
                                    color: Colors.black,
                                  ),
                                ),
                                numeric: true,
                              ),
                              DataColumn(
                                label: Text(
                                  'Player username',
                                  style: const TextStyle(
                                    fontSize: 20,
                                    color: Colors.black,
                                  ),
                                ),
                              ),
                              DataColumn(
                                label: Text(
                                  'Score',
                                  style: const TextStyle(
                                    fontSize: 20,
                                    color: Colors.black,
                                  ),
                                ),
                                numeric: true,
                              ),
                              DataColumn(
                                label: Text(
                                  'Correct answers',
                                  style: const TextStyle(
                                    fontSize: 20,
                                    color: Colors.black,
                                  ),
                                ),
                                numeric: true,
                              ),
                              DataColumn(
                                label: Text(
                                  'Worng answers',
                                  style: const TextStyle(
                                    fontSize: 20,
                                    color: Colors.black,
                                  ),
                                ),
                                numeric: true,
                              ),
                              DataColumn(
                                label: Text(
                                  'Average answer time',
                                  style: const TextStyle(
                                    fontSize: 20,
                                    color: Colors.black,
                                  ),
                                ),
                                numeric: true,
                              )
                            ],
                            rows: List.generate(_results.length, (index) {
                              final results = _results[index];
                              return DataRow(
                                selected: true,
                                cells: [
                                  DataCell(Text(
                                    (index + 1).toString(),
                                    style: const TextStyle(
                                      fontSize: 20,
                                      color: Colors.black,
                                    ),
                                  )),
                                  DataCell(Text(
                                    results.getUsername(),
                                    style: const TextStyle(
                                      fontSize: 20,
                                      color: Colors.black,
                                    ),
                                  )),
                                  DataCell(Text(
                                    0.toString(),
                                    style: const TextStyle(
                                      fontSize: 20,
                                      color: Colors.black,
                                    ),
                                  )),
                                  DataCell(Text(
                                    results.getCorrectAnswersCount().toString(),
                                    style: const TextStyle(
                                      fontSize: 20,
                                      color: Colors.black,
                                    ),
                                  )),
                                  DataCell(Text(
                                    results.getWorngAnswersCount().toString(),
                                    style: const TextStyle(
                                      fontSize: 20,
                                      color: Colors.black,
                                    ),
                                  )),
                                  DataCell(Text(
                                    results.getAverageAnswerTime().toString(),
                                    style: const TextStyle(
                                      fontSize: 20,
                                      color: Colors.black,
                                    ),
                                  )),
                                ],
                              );
                            }),
                          ),
                        ),
                      ),
                    ),
                  ),
                ),
              ),
            ),
            Container(
              height: MediaQuery.of(context).size.height * 0.15,
              width: MediaQuery.of(context).size.width,
              color: Color.fromARGB(255, 29, 45, 68),
              padding: const EdgeInsets.all(16.0),
              child: Align(
                alignment: Alignment.bottomCenter,
                child: Container(
                  padding: const EdgeInsets.all(16.0),
                  decoration: BoxDecoration(
                    color: Color.fromARGB(255, 50, 101, 172),
                    borderRadius: BorderRadius.circular(32.0),
                  ),
                  child: ElevatedButton(
                    style: ElevatedButton.styleFrom(
                      minimumSize: Size(90, 64.0),
                      backgroundColor: Color.fromARGB(255, 196, 255, 249),
                      shape: RoundedRectangleBorder(
                        borderRadius: BorderRadius.circular(32.0),
                      ),
                    ),
                    child: Text(
                      "Return to main menu",
                      style: TextStyle(fontSize: 20, color: Colors.black),
                    ),
                    onPressed: () async {
                      Navigator.pushReplacement(
                          context,
                          MaterialPageRoute(
                              builder: (_) =>
                                  HomePage(socketService: _socketService)));
                    },
                  ),
                ),
              ),
            ),
          ],
        ),
      ),
    );
  }
}
