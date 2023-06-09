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

// ignore_for_file: prefer_const_constructors

// ignore: must_be_immutable
int GET_CATEGORIES_CODE = 6;
int CREATE_ROOM_REQUEST_CODE = 11;
int ERROR_CODE = 99;

class HomePage extends StatefulWidget {
  final SocketService socketService;

  const HomePage({super.key, required this.socketService});

  @override
  _HomePage createState() => _HomePage(socketService);
}

class _HomePage extends State<HomePage> {
  final SocketService _socketService;
  final List<Category> _categories = [];
  late TextEditingController maxNumberOfPlayers;
  late TextEditingController numberOfQuestions;
  late TextEditingController maxTime;

  _HomePage(this._socketService);

  @override
  void initState() {
    maxNumberOfPlayers = TextEditingController();
    numberOfQuestions = TextEditingController();
    maxTime = TextEditingController();

    maxNumberOfPlayers.text = "2";
    numberOfQuestions.text = "1";
    maxTime.text = "1";

    super.initState();
    getCategories().then((result) {
      setState(() {});
    });
  }

  Future<void> getCategories() async {
    _socketService.sendMessage(Message(GET_CATEGORIES_CODE, {}));
    final Message response = await _socketService.receiveMessage();

    Map<String, dynamic> data = response.getData();
    for (var categoryString in data["publicCategories"]) {
      _categories
          .add(Category(categoryString[1], categoryString[0], true));
    }
  }

  @override
  Widget build(BuildContext context) {
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
      body: SingleChildScrollView(
        child: Column(children: [
          for (Category category in _categories)
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
                        onPressed: () {
                          openDialg(category);
                        },
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

  Future openDialg(Category category) => showDialog(
      context: context,
      builder: (context) => AlertDialog(
            title: Text(category.getName()),
            content: Column(children: [
              Text("Max number of players: "),
              IncrementDecrementButton(
                  controller: maxNumberOfPlayers, minValue: 2),
              Text("Number of Questions: "),
              IncrementDecrementButton(
                  controller: numberOfQuestions, minValue: 1),
              Text("Max timr per Questions: "),
              IncrementDecrementButton(controller: maxTime, minValue: 1),
            ]),
            actions: [
              TextButton(
                  onPressed: (() {
                    create(category);
                  }),
                  child: Text("CREATE")),
              TextButton(onPressed: cancel, child: Text("CANCEL")),
            ],
          ));

  void cancel() {
    Navigator.of(context).pop();
  }

  void create(Category category) async {
    if (await createRoom(category)) {
      Navigator.pushReplacement(
        context,
        MaterialPageRoute(
          builder: (_) => RoomPage(
            socketService: widget.socketService,
            admin: true,
          ),
        ),
      );
    }
  }

  Future<bool> createRoom(Category category) async {
    Map<String, dynamic> data = {
      "categorieId": category.getId(),
      "maxPlayers": int.parse(maxNumberOfPlayers.text),
      "questionCount": int.parse(numberOfQuestions.text),
      "answerTimeout": int.parse(maxTime.text),
      "name": ""
    };
    _socketService.sendMessage(Message(CREATE_ROOM_REQUEST_CODE, data));
    final Message response = await _socketService.receiveMessage();
    return response.getCode() != ERROR_CODE;
  }
}
