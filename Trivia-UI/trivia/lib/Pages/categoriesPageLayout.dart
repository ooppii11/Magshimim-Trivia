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
int GET_CATEGORIES_RESPONSE_CODE = 6;

class CategoriesPage extends StatefulWidget {
  final SocketService socketService;
  final List<Category> categories;
  final Function disposeCallback;

  CategoriesPage(
      {Key? key,
      required this.socketService,
      required this.categories,
      required this.disposeCallback})
      : super(key: key);

  @override
  _CategoriesPage createState() => _CategoriesPage(socketService, categories);
}

class _CategoriesPage extends State<CategoriesPage> {
  late TextEditingController maxNumberOfPlayers;
  late TextEditingController numberOfQuestions;
  late TextEditingController maxTime;
  final SocketService _socketService;
  final List<Category> _categories;

  _CategoriesPage(this._socketService, this._categories);

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

  Future create(Category category) async {
    Message response = await createRoom(category);
    if (response.getCode() != ERROR_CODE) {
      Navigator.of(context, rootNavigator: true).pop();
      widget.disposeCallback();
      Navigator.pushReplacement(
        context,
        MaterialPageRoute(
          builder: (_) => RoomPage(
            socketService: _socketService,
            admin: true,
            roomId: response.getData()["roomId"],
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

    super.initState();
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
