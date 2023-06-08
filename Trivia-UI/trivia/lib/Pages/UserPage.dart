import 'package:trivia/Pages/HomePage.dart';
import 'package:trivia/Pages/leaderBoardPage.dart';
import 'package:trivia/SocketService.dart';
import 'package:flutter/material.dart';
import 'package:trivia/Pages/loginPage.dart';

class UserPage extends StatefulWidget {
  final SocketService socketService;

  const UserPage({super.key, required this.socketService});

  @override
  _UserPage createState() => _UserPage();
}

class _UserPage extends State<UserPage> {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
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
      // User page content:
      // TODO: add a card that is on the top center and has user private stats
      // TODO: add a container that has user last five games
      
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
    );
  }
}
