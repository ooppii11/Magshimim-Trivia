import 'package:trivia/Pages/HomePage.dart';
import 'package:trivia/Pages/leaderBoardPage.dart';
import 'package:trivia/SocketService.dart';
import 'package:flutter/material.dart';
import 'package:trivia/Pages/loginPage.dart';
import 'package:trivia/message.dart';

class UserPage extends StatefulWidget {
  final SocketService socketService;

  const UserPage({super.key, required this.socketService});

  @override
  _UserPage createState() => _UserPage();
}

class _UserPage extends State<UserPage> {
  late List<Map<String, dynamic>> _history;
  late Map<String, dynamic> _statistics;

  _UserPage()
  {
    this._history = [];
    this._statistics = {}; 
    getHistory();
    getStatistics();
  }

  void getHistory() async {
    
  }
  
  void getStatistics() async {

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
                  onPressed: () {
                    Navigator.pushReplacement(
                        context,
                        MaterialPageRoute(
                            builder: (_) => LoginPage(
                                  socketService: widget.socketService,
                                )));
                  }),
            ),
          ]),
        body: SingleChildScrollView(
          child: Center(
            child: Column(
              children: [
                Padding(
                  padding: EdgeInsets.symmetric(horizontal: 16, vertical: 16),
                  child: Column(
                    children: [
                      Text(
                        'STATS',
                        style: TextStyle(fontSize: 20, fontWeight: FontWeight.bold),
                      ),
                      SizedBox(height: 16),
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
                          child: DefaultTextStyle(
                            style: const TextStyle(color: Colors.black),
                            child: DataTable(
                              dataTextStyle: const TextStyle(color: Colors.black),
                              columns: const [
                                DataColumn(
                                  label: Text('Statistics Name'),
                                ),
                                DataColumn(
                                  label: Text('User Results'),
                                )
                              ],
                              rows: _statistics.entries.map((entry) {
                                return DataRow(
                                  cells: [
                                    DataCell(Text(entry.key)),
                                    DataCell(Text(entry.value.toString())),
                                  ],
                                );
                              }).toList(),
                            ),
                          ),
                        ),
                      ),
                    ],
                  ),
                ),
                SizedBox(height: 16),
                Padding(
                  padding: EdgeInsets.symmetric(horizontal: 16),
                  child: Column(
                    children: [
                      Text(
                        'HISTORY',
                        style: TextStyle(fontSize: 20, fontWeight: FontWeight.bold),
                      ),
                      SizedBox(height: 16),
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
                          child: DefaultTextStyle(
                            style: const TextStyle(color: Colors.black),
                            child: DataTable(
                              dataTextStyle: const TextStyle(color: Colors.black),
                              columns: const [
                                DataColumn(
                                  label: Text('Num'),
                                ),
                                DataColumn(
                                  label: Text('Category'),
                                ),
                                DataColumn(
                                  label: Text('Score'),
                                ),
                              ],
                              rows: _history.map((entry) {
                                return DataRow(
                                  cells: [
                                    DataCell(Text((_history.indexOf(entry) + 1).toString())),
                                    DataCell(Text(entry['category'].toString())),
                                    DataCell(Text(entry['score'].toString())),
                                  ],
                                );
                              }).toList(),
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
            const BottomNavigationBarItem(icon: Icon(Icons.add_box), label: ''),
            const BottomNavigationBarItem(
                icon: Icon(Icons.leaderboard_rounded), label: ''),
            BottomNavigationBarItem(
                icon: Icon(Icons.home, color: Colors.grey[600]), label: ''),
          ],
          onTap: (value) {
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
}
