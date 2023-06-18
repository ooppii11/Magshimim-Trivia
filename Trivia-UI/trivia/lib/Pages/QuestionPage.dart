import 'package:trivia/Pages/RightWorng.dart';
import 'dart:async';
import 'package:flutter/material.dart';
import 'package:trivia/Pages/HomePage.dart';
import 'package:trivia/Pages/categoriesPageLayout.dart';
import 'package:trivia/Question.dart';
import 'package:trivia/SocketService.dart';
import 'package:trivia/message.dart';
import 'package:trivia/Pages/WaitingPage.dart';

int SUBMIT_ANSWER_REQUEST_CODE = 21;
int GET_QUESTION_REQUEST_CODE = 23;
int LEAVE_GAME_REQUEST_CODE = 22;

class QuestionPage extends StatefulWidget {
  final SocketService socketService;
  final int numberOfQuestion;
  final int currentQuestionNumber;
  final double maxTimePerQuestion;

  const QuestionPage(
      {super.key,
      required this.socketService,
      required this.maxTimePerQuestion,
      required this.currentQuestionNumber,
      required this.numberOfQuestion});

  @override
  _QuestionPage createState() => _QuestionPage(socketService,
      maxTimePerQuestion, numberOfQuestion, currentQuestionNumber);
}

class _QuestionPage extends State<QuestionPage> {
  final SocketService _socketService;
  final int _numberOfQuestion;
  final int _currentQuestionNumber;
  final double _maxTimePerQuestion;
  late Timer _timer;
  late double _countdownDuration;

  late Question _question = Question("Error", {});

  _QuestionPage(this._socketService, this._maxTimePerQuestion,
      this._numberOfQuestion, this._currentQuestionNumber) {
    _countdownDuration = _maxTimePerQuestion;
  }

  @override
  void initState() {
    startTimer();
    getQuetion();
    super.initState();
  }

  void startTimer() {
    const double interval = 0.1;
    _timer = Timer.periodic(Duration(milliseconds: (interval * 1000).toInt()),
        (Timer timer) {
      _countdownDuration -= interval;

      if (_countdownDuration <= 0) {
        timer.cancel();
        submitAnswer(5);
        Navigator.pushReplacement(
            context,
            MaterialPageRoute(
                builder: (_) => RightWorngPage(
                    socketService: _socketService,
                    isRight: false,
                    numberOfQuestion: _numberOfQuestion,
                    currenQuestionNumber: _currentQuestionNumber + 1,
                    timeOut: _maxTimePerQuestion)));
      }
    });
  }

  @override
  void dispose() {
    _timer.cancel();
    super.dispose();
  }

  Future<void> getQuetion() async {
    _socketService.sendMessage(Message(GET_QUESTION_REQUEST_CODE, {}));
    Message response = await _socketService.receiveMessage();
    if (response.getCode() != ERROR_CODE) {
      Question question = Question(response.getData()["Question"],
          {for (var item in response.getData()["Answers"]) item[0]: item[1]});

      setState(() {
        _question = question;
      });
    }
  }

  Future<void> leaveGame() async {
    _socketService.sendMessage(Message(LEAVE_GAME_REQUEST_CODE, {}));
    Message response = await _socketService.receiveMessage();
    if (response != ERROR_CODE) {
      Navigator.pushReplacement(
          context,
          MaterialPageRoute(
              builder: (_) => HomePage(socketService: _socketService)));
    }
  }

  Future<void> submitAnswer(int answerId) async {
    _socketService.sendMessage(
        Message(SUBMIT_ANSWER_REQUEST_CODE, {"answerIndex": answerId}));
    Message response = await _socketService.receiveMessage();
    Navigator.pushReplacement(
        context,
        MaterialPageRoute(
            builder: (_) => WaitingPage(
                socketService: _socketService,
                time: _countdownDuration,
                isRight: response.getData()["correctAnswerIndex"] == answerId,
                numberOfQuestion: _numberOfQuestion,
                currenQuestionNumber: _currentQuestionNumber + 1,
                timeOut: _maxTimePerQuestion)));
  }

  @override
  Widget build(BuildContext context) {
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
      body: Column(
          children: [
            Container(
              height: MediaQuery.of(context).size.height * 0.25,
              width: MediaQuery.of(context).size.width,
              color: const Color.fromARGB(255, 111, 156, 235),
              padding: const EdgeInsets.all(16.0),
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  Align(
                    alignment: Alignment.center,
                    child: SizedBox(height: 8.0),
                  ),
                  Align(
                    alignment: Alignment.center,
                    child: Text(
                    _question.getQuestion(),
                    style: TextStyle(
                      fontSize: 28,
                      fontWeight: FontWeight.bold,
                      color: Colors.black,
                    ),
                  ),
                  ),
                ],
              ),
            ),
            Expanded(
              child: Container(
                width: MediaQuery.of(context).size.width,
                color: const Color.fromARGB(255, 29, 45, 68),
                padding: const EdgeInsets.all(16.0),
                child:
                    Column(mainAxisAlignment: MainAxisAlignment.center, children: [
                  for (MapEntry<int, String> answer in _question.getAnswers().entries)
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
                            submitAnswer(answer.key);
                          },
                          child: Column(
                            children: [
                              Padding(
                                padding: const EdgeInsets.all(0.0),
                                child: Text(
                                  answer.value,
                                  style: const TextStyle(
                                      color: Colors.white, fontSize: 25),
                                ),
                              ),
                            ],
                          ),
                        ),
                      ),
                    ),
                ]),
              ),
            )
          ],
        ),
     // ),
    );
  }
}
