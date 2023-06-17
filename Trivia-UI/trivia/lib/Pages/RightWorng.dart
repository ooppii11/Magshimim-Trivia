import 'package:flutter/material.dart';
import 'package:trivia/SocketService.dart';
import 'package:trivia/Pages/QuestionPage.dart';

class RightWorngPage extends StatefulWidget {
  final SocketService socketService;
  final bool isRight;
  final int numberOfQuestion;
  final int currenQuestionNumber;

  const RightWorngPage({
    super.key,
    required this.socketService,
    required this.isRight,
    required this.numberOfQuestion,
    required this.currenQuestionNumber,
  });

  @override
  _RightWorngPage createState() => _RightWorngPage(
      socketService, isRight, currenQuestionNumber, numberOfQuestion);
}

class _RightWorngPage extends State<RightWorngPage> {
  final SocketService socketService;
  final bool _isRight;
  final int _numberOfQuestion;
  final int _currenQuestionNumber;

  _RightWorngPage(this.socketService, this._isRight,
      this._currenQuestionNumber, this._numberOfQuestion);

  Future delay() async {
    await new Future.delayed(new Duration(seconds: 3), () {
      if (_currenQuestionNumber != _numberOfQuestion) {
        Navigator.pushReplacement(
          context,
          MaterialPageRoute(
              builder: (_) => QuestionPage(
                  socketService: socketService,
                  currenQuestionNumber: _currenQuestionNumber,
                  numberOfQuestion: _numberOfQuestion)),
        );
      } else {
        /*Navigator.pushReplacement(
          context,
          MaterialPageRoute(
            builder: (_) => ResultPage(
              socketService: widget.socketService,
            ),
          ),
        );*/
      }
    });
  }

  Widget correct() {
    return Scaffold(
      body: SingleChildScrollView(
          scrollDirection: Axis.vertical,
          child: Center(
              child: Column(children: [
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
    );
  }

  Widget worng() {
    return Scaffold(
      body: SingleChildScrollView(
          scrollDirection: Axis.vertical,
          child: Center(
              child: Column(children: [
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
