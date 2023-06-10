import 'dart:async';
import 'package:trivia/Pages/roomPage.dart';
import 'package:trivia/components/increment_decrement_button.dart';
import 'package:trivia/Pages/UserPage.dart';
import 'package:trivia/Pages/loginPage.dart';
import 'package:trivia/Pages/leaderBoardPage.dart';
import 'package:trivia/category.dart';
import 'package:trivia/SocketService.dart';
import 'package:flutter/material.dart';
import 'package:trivia/message.dart';
import 'package:trivia/Pages/categoriesPageLayout.dart';

// ignore_for_file: prefer_const_constructors

// ignore: must_be_immutable
int GET_CATEGORIES_CODE = 6;
int CREATE_ROOM_REQUEST_CODE = 12;
int ERROR_CODE = 99;

class HomePage extends StatefulWidget {
  final SocketService socketService;

  const HomePage({super.key, required this.socketService});

  @override
  _HomePage createState() => _HomePage(socketService);
}

class _HomePage extends State<HomePage> with SingleTickerProviderStateMixin {
  final SocketService _socketService;
  _HomePage(this._socketService);

  @override
  void initState() {
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: DefaultTabController(
        length: 2,
        child: Scaffold(
          bottomNavigationBar: BottomNavigationBar(
              type: BottomNavigationBarType.fixed,
              items: [
                BottomNavigationBarItem(
                    icon: Icon(Icons.person, color: Colors.grey[600]),
                    label: ''),
                BottomNavigationBarItem(icon: Icon(Icons.add_box), label: ''),
                BottomNavigationBarItem(
                    icon: Icon(Icons.leaderboard_rounded), label: ''),
                BottomNavigationBarItem(
                    icon: Icon(
                      Icons.home,
                      color: Colors.blue,
                    ),
                    label: ''),
              ],
              onTap: (value) {
                if (value == 0) {
                  Navigator.pushReplacement(
                    context,
                    MaterialPageRoute(
                      builder: (_) => UserPage(
                        socketService: widget.socketService,
                      ),
                    ),
                  );
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
              }),
          appBar: AppBar(
              bottom: TabBar(
                indicator: BoxDecoration(
                  borderRadius: BorderRadius.circular(
                    25.0,
                  ),
                  color: Colors.green,
                ),
                labelColor: Colors.white,
                unselectedLabelColor: Colors.black,
                tabs: const [
                  Tab(
                    icon: Icon(Icons.category),
                  ),
                  Tab(
                    text: 'Rooms',
                  ),
                ],
              ),
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
          body: TabBarView(
            children: [
              CategoriesPage(socketService: _socketService),
              Icon(Icons.directions_car),
            ],
          ),
        ),
      ),
    );
  }
}
