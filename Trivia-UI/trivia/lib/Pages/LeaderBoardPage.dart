import 'package:trivia/SocketService.dart';
import 'package:flutter/material.dart';
import 'package:trivia/Pages/loginPage.dart';
import 'package:trivia/Pages/UserPage.dart';
import 'package:trivia/Pages/HomePage.dart';

class LeaderBoardPage extends StatefulWidget {
  final SocketService socketService;

  LeaderBoardPage({required this.socketService});

  @override
  _LeaderBoardPage createState() => _LeaderBoardPage();
}

class _LeaderBoardPage extends State<LeaderBoardPage> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
        bottomNavigationBar: BottomNavigationBar(
            type: BottomNavigationBarType.fixed,
            items: [
              BottomNavigationBarItem(
                  icon: Icon(Icons.person, color: Colors.grey[600]), label: ''),
              BottomNavigationBarItem(icon: Icon(Icons.add_box), label: ''),
              BottomNavigationBarItem(
                  icon: Icon(
                    Icons.leaderboard_rounded,
                    color: Colors.blue,
                  ),
                  label: ''),
              BottomNavigationBarItem(
                  icon: Icon(
                    Icons.home,
                  ),
                  label: ''),
            ],
            onTap: (value) {
              if (value == 0)
                Navigator.pushReplacement(
                  context,
                  MaterialPageRoute(
                    builder: (_) => UserPage(
                      socketService: widget.socketService,
                    ),
                  ),
                );
              if (value == 3)
                Navigator.pushReplacement(
                  context,
                  MaterialPageRoute(
                    builder: (_) => HomePage(
                      socketService: widget.socketService,
                    ),
                  ),
                );
            }),
        appBar: AppBar(
            backgroundColor: Colors.transparent,
            elevation: 0,
            actions: <Widget>[
              Padding(
                padding: EdgeInsets.only(right: 20.0),
                child: IconButton(
                    icon: Icon(
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
          child: Column(children: [
            Text("Leadrboard"),
            Container(
              decoration: BoxDecoration(
                  borderRadius: BorderRadius.circular(20.0),
                  gradient: LinearGradient(colors: [
                    Colors.yellow.shade600,
                    Colors.orange,
                    Colors.red
                  ])),
              child: Padding(
                padding: const EdgeInsets.all(2.0),
                child: Container(
                  height: 600,
                ),
              ),
            ),
          ]),
        ));
  }
}
