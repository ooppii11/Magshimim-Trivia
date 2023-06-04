import 'dart:async';
import 'package:trivia/Pages/UserPage.dart';
import 'package:trivia/Pages/loginPage.dart';
import 'package:trivia/Pages/leaderBoardPage.dart';
import 'package:trivia/category.dart';
import 'package:trivia/SocketService.dart';
import 'package:flutter/material.dart';
import 'package:trivia/message.dart';

// ignore_for_file: prefer_const_constructors

// ignore: must_be_immutable
int GET_CATEGORIES_CODE = 7;

class HomePage extends StatefulWidget {
  final SocketService socketService;

  const HomePage({super.key, required this.socketService});

  @override
  _HomePage createState() => _HomePage(socketService);
}

class _HomePage extends State<HomePage> {
  final SocketService _socketService;
  List<Category> _categories = [];

  _HomePage(this._socketService);

  @override
  void initState() {
    super.initState();
    //getCategories().then((value) => {print('Async done')});
    getCategories()
        // as suggested in the comment
        // .whenComplete() {
        // or
        .then((result) {
      print('Async done');
      setState(() {});
    });
  }

  Future<void> getCategories() async {
    _socketService.sendMessage(Message(GET_CATEGORIES_CODE, {}));
    final Message response = await _socketService.receiveMessage();

    Map<String, dynamic> data = response.getData();
    for (var categoryString in data["publicCategories"]) {
      print("object");
      this
          ._categories
          .add(Category(categoryString[0], categoryString[1], true));
    }
  }

  @override
  Widget build(BuildContext context) {
    print("object3");
    return Scaffold(
      backgroundColor: Colors.white,
      bottomNavigationBar: BottomNavigationBar(
          type: BottomNavigationBarType.fixed,
          items: [
            BottomNavigationBarItem(
                icon: Icon(Icons.person, color: Colors.grey[600]), label: ''),
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
          for (Category category in this._categories)
            Padding(
                padding: const EdgeInsets.only(
                  left: 15.0,
                  right: 15.0,
                  top: 15,
                  bottom: 0,
                ),
                child: Container(
                    height: 125,
                    width: 250,
                    decoration: BoxDecoration(
                      color: Colors.blue,
                      borderRadius: BorderRadius.circular(0),
                    ),
                    child: TextButton(
                        onPressed: () {},
                        child: Column(
                          children: [
                            Padding(
                              padding: const EdgeInsets.all(8.0),
                              child: Text(
                                category.getName(),
                                style: TextStyle(
                                    color: Colors.white, fontSize: 25),
                              ),
                            ),
                            Padding(
                              padding: const EdgeInsets.all(8.0),
                              child: Text(
                                category.getPermission()
                                    ? "Permission: Public"
                                    : "Permission:Private",
                                style: TextStyle(
                                    color: Colors.white, fontSize: 10),
                              ),
                            )
                          ],
                        ))))
        ]),
      ),
    );
  }
}
