import 'dart:async';
import 'package:trivia/Pages/roomPage.dart';
import 'package:trivia/components/increment_decrement_button.dart';
import 'package:trivia/category.dart';
import 'package:trivia/SocketService.dart';
import 'package:flutter/material.dart';
import 'package:trivia/message.dart';

// ignore_for_file: prefer_const_constructors

// ignore: must_be_immutable
int GET_CATEGORIES_CODE = 7;
int CREATE_ROOM_REQUEST_CODE = 12;
int ERROR_CODE = 99;

class CategoriesPage extends StatefulWidget {
  final SocketService socketService;

  const CategoriesPage({super.key, required this.socketService});

  @override
  _CategoriesPage createState() => _CategoriesPage(socketService);
}

class _CategoriesPage extends State<CategoriesPage> {
  final SocketService _socketService;
  final List<Category> _categories = [];
  late TextEditingController maxNumberOfPlayers;
  late TextEditingController numberOfQuestions;
  late TextEditingController maxTime;

  _CategoriesPage(this._socketService);

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
    Navigator.of(context, rootNavigator: true).pop();
  }

  void create(Category category) async {
    Message response = await createRoom(category);
    if (response.getCode() != ERROR_CODE ) {
      Navigator.pushReplacement(
        context,
        MaterialPageRoute(
          builder: (_) => RoomPage(
            socketService: widget.socketService,
            admin: true,
            roomId: int.parse(response.getData()["roomId"]),
          ),
        ),
      );
    }
  }

  @override
  void initState() {
    maxNumberOfPlayers = TextEditingController();
    numberOfQuestions = TextEditingController();
    maxTime = TextEditingController();

    maxNumberOfPlayers.text = "2";
    numberOfQuestions.text = "1";
    maxTime.text = "1";
    getCategories().then((result) {
      setState(() {});
    });
  }

  Future<void> getCategories() async {
    _socketService.sendMessage(Message(GET_CATEGORIES_CODE, {}));
    final Message response = await _socketService.receiveMessage();

    Map<String, dynamic> data = response.getData();
    for (var categoryString in data["publicCategories"]) {
      _categories.add(Category(categoryString[1], categoryString[0], true));
    }
  }

  Future<Message> createRoom(Category category) async {
    Map<String, dynamic> data = {
      "categorieId": category.getId(),
      "maxUsers": int.parse(maxNumberOfPlayers.text),
      "questionCount": int.parse(numberOfQuestions.text),
      "answerTimeout": int.parse(maxTime.text),
      "roomName": ""
    };
    _socketService.sendMessage(Message(CREATE_ROOM_REQUEST_CODE, data));
    final Message response = await _socketService.receiveMessage();
    return response;
    //response.getCode() != ERROR_CODE;
  }

  @override
  Widget build(BuildContext context) {
    return SingleChildScrollView(
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
                height: 50,
                width: 300,
                decoration: BoxDecoration(
                  color: Colors.blue,
                  borderRadius: BorderRadius.circular(
                    25.0,
                  ),
                ),
                child: TextButton(
                    onPressed: () {
                      openDialg(category);
                    },
                    child: Column(children: [
                      Padding(
                        padding: const EdgeInsets.all(0.0),
                        child: Text(
                          category.getName(),
                          style: TextStyle(color: Colors.white, fontSize: 25),
                        ),
                      ),
                      Padding(
                        padding: const EdgeInsets.all(0),
                        child: Text(
                          category.getPermission()
                              ? "Permission: Public"
                              : "Permission:Private",
                          style: TextStyle(color: Colors.white, fontSize: 10),
                        ),
                      )
                    ]))))
    ]));
  }
}
