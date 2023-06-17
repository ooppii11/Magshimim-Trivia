import 'package:flutter/material.dart';
import 'package:trivia/Pages/HomePage.dart';
import 'package:trivia/Pages/categoriesPageLayout.dart';
import 'package:trivia/Question.dart';
import 'package:trivia/SocketService.dart';
import 'package:trivia/message.dart';

int SUBMIT_ANSWER_REQUEST_CODE = 21;
int GET_QUESTION_REQUEST_CODE = 23;
int LEAVE_GAME_REQUEST_CODE = 22;

class QuestionPage extends StatefulWidget {
  final SocketService socketService;
  final int numberOfQuestion;
  final int currenQuestionNumber;

  const QuestionPage(
      {super.key,
      required this.socketService,
      required this.currenQuestionNumber,
      required this.numberOfQuestion});

  @override
  _QuestionPage createState() =>
      _QuestionPage(socketService, numberOfQuestion, currenQuestionNumber);
}

class _QuestionPage extends State<QuestionPage> {
  final SocketService _socketService;
  final int _numberOfQuestion;
  final int _currenQuestionNumber;
  late Question _question = Question("error", {});

  _QuestionPage(
      this._socketService, this._numberOfQuestion, this._currenQuestionNumber);

  @override
  void initState() {
    getQuetion();
    super.initState();
  }

  Future<void> getQuetion() async {
    _socketService.sendMessage(Message(GET_QUESTION_REQUEST_CODE, {}));
    Message response = await _socketService.receiveMessage();
    Question question = new Question(
        response.getData()["Question"],
        Map.fromIterable(response.getData()["Answers"],
            key: (item) => item[0], value: (item) => item[1]));

    setState(() {
      _question = question;
    });
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
    //stopTimer();
    _socketService.sendMessage(
        Message(SUBMIT_ANSWER_REQUEST_CODE, {"answerIndex": answerId}));
    Message response = await _socketService.receiveMessage();
    //navigate to wait page
    //response.getData()["correctAnswerIndex"] == answerId
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        appBar: AppBar(
            backgroundColor: Colors.transparent,
            elevation: 0,
            actions: <Widget>[
              Padding(
                  padding: const EdgeInsets.only(top: 15),
                  child: Container(
                      height: 40,
                      decoration: BoxDecoration(
                        color: Colors.redAccent,
                        borderRadius: BorderRadius.circular(
                          12.5,
                        ),
                      ),
                      child: TextButton(
                        child: Text(
                          "Leave game",
                          style: TextStyle(fontSize: 25, color: Colors.white),
                        ),
                        onPressed: () async {
                          await leaveGame();
                        },
                      )))
            ]),
        body: Stack(children: [
          SingleChildScrollView(
              scrollDirection: Axis.vertical,
              child: Center(
                  child: Column(children: [
                Container(
                  margin: EdgeInsets.all(100.0),
                  decoration:
                      BoxDecoration(color: Colors.blue, shape: BoxShape.circle),
                ),
                Text(_question.getQuestion()),
                Column(children: [
                  for (MapEntry<int, String> answer
                      in _question.getAnswers().entries)
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
                                child: Column(children: [
                                  Padding(
                                    padding: const EdgeInsets.all(0.0),
                                    child: Text(
                                      answer.value,
                                      style: TextStyle(
                                          color: Colors.white, fontSize: 25),
                                    ),
                                  ),
                                ]))))
                ])
              ])))
        ]));
  }
}
