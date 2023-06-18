import 'package:flutter/material.dart';
import 'package:trivia/Pages/ResultPage.dart';
import 'package:trivia/SocketService.dart';
import 'package:trivia/Pages/QuestionPage.dart';
import 'package:trivia/Pages/HomePage.dart';
import 'package:trivia/message.dart';
import 'dart:async';

class RightWorngPage extends StatefulWidget {
  final SocketService socketService;
  final bool isRight;
  final int numberOfQuestion;
  final int currenQuestionNumber;
  final double timeOut;

  const RightWorngPage({
    super.key,
    required this.socketService,
    required this.isRight,
    required this.numberOfQuestion,
    required this.currenQuestionNumber,
    required this.timeOut,
  });

  @override
  _RightWorngPage createState() => _RightWorngPage(
      socketService, isRight, currenQuestionNumber, numberOfQuestion, timeOut);
}

class _RightWorngPage extends State<RightWorngPage> {
  final SocketService _socketService;
  final bool _isRight;
  final int _numberOfQuestion;
  final int _currenQuestionNumber;
  final double _timeOut;
  late Timer _timer;

  _RightWorngPage(this._socketService, this._isRight,
      this._currenQuestionNumber, this._numberOfQuestion, this._timeOut);

  @override
  void initState() {
    delay();
    super.initState();
  }

  @override
  void dispose() {
    _timer.cancel();
    super.dispose();
  }

  Future delay() async {
    _timer = Timer(const Duration(seconds: 3), () {
      if (_currenQuestionNumber != _numberOfQuestion) {
        Navigator.pushReplacement(
          context,
          MaterialPageRoute(
              builder: (_) => QuestionPage(
                  socketService: _socketService,
                  currentQuestionNumber: _currenQuestionNumber,
                  numberOfQuestion: _numberOfQuestion,
                  maxTimePerQuestion: _timeOut)),
        );
      } else {
        Navigator.pushReplacement(
          context,
          MaterialPageRoute(
              builder: (_) => ResultPage(socketService: _socketService)),
        );
      }
    });
  }

  Future<void> leaveGame() async {
    _socketService.sendMessage(Message(22, {}));
    Message response = await _socketService.receiveMessage();
    if (response != 99) {
      Navigator.pushReplacement(
          context,
          MaterialPageRoute(
              builder: (_) => HomePage(socketService: _socketService)));
    }
  }

  Widget correct() {
    return Scaffold(
      appBar: AppBar(
            backgroundColor: Colors.transparent,
            elevation: 0,
            actions: <Widget>[
              Padding(
                  padding: const EdgeInsets.only(top: 15, bottom: 15),
                  child: Container(
                      height: 20,
                      decoration: BoxDecoration(
                        color: Colors.redAccent,
                        borderRadius: BorderRadius.circular(
                          12.5,
                        ),
                      ),
                      child: TextButton(
                        child: const Text(
                          "Leave Game",
                          style: TextStyle(fontSize: 20, color: Colors.white),
                        ),
                        onPressed: () async {
                          await leaveGame();
                        },
                      )))
            ]),
      body: Container(
        width: double.infinity,
        height: double.infinity,
        color: const Color.fromARGB(255, 29, 45, 68),
        child: const SingleChildScrollView(
          scrollDirection: Axis.vertical,
          child: const Center(
              child: Column(
                mainAxisAlignment: MainAxisAlignment.center,
                crossAxisAlignment: CrossAxisAlignment.center,
                children: [
            Icon(
              Icons.check_circle_outline_outlined,
              size: 100,
              color: Colors.green,
            ),
            Text(
              "Correct answer",
              style: TextStyle(color: Colors.green, fontSize: 30),
            ),
          ]))),
      ),
    );
  }

  Widget worng() {
    return Scaffold(
      appBar: AppBar(
            backgroundColor: Colors.transparent,
            elevation: 0,
            actions: <Widget>[
              Padding(
                  padding: const EdgeInsets.only(top: 15, bottom: 15),
                  child: Container(
                      height: 20,
                      decoration: BoxDecoration(
                        color: Colors.redAccent,
                        borderRadius: BorderRadius.circular(
                          12.5,
                        ),
                      ),
                      child: TextButton(
                        child: const Text(
                          "Leave Game",
                          style: TextStyle(fontSize: 20, color: Colors.white),
                        ),
                        onPressed: () async {
                          await leaveGame();
                        },
                      )))
            ]),
      body: Container(
        width: double.infinity,
        height: double.infinity,
        color: const Color.fromARGB(255, 29, 45, 68),
        child: const SingleChildScrollView(
          scrollDirection: Axis.vertical,
          child: const Center(
              child: Column(
                mainAxisAlignment: MainAxisAlignment.center,
                crossAxisAlignment: CrossAxisAlignment.center,
                children: [
            Icon(
              Icons.error_outline,
              size: 150,
              color: Colors.red,
            ),
            Text(
              "Worng answer",
              style: TextStyle(color: Colors.red, fontSize: 30),
            ),
          ]))),
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    if (_isRight) {
      return correct();
    }
    return worng();
  }
}
