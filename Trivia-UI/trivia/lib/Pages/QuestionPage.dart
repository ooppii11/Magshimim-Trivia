import 'package:trivia/Question.dart';
import 'package:trivia/message.dart';
import 'package:trivia/SocketService.dart';
import 'package:flutter/material.dart';

int SUBMIT_ANSWER_REQUEST_CODE = 0;
int GET_QUESTION_REQUEST_CODE = 0;

class QuestionPage extends StatefulWidget {
  final SocketService socketService;

  const QuestionPage({super.key, required this.socketService});

  @override
  _QuestionPage createState() => _QuestionPage(socketService);
}

class _QuestionPage extends State<QuestionPage> {
  final SocketService _socketService;
  late Question _question;

  _QuestionPage(this._socketService);

  @override
  @override
  void initState() {
    super.initState();
  }

  Future<void> getQuetion() async {
    _socketService.sendMessage(Message(GET_QUESTION_REQUEST_CODE, {}));
    Message response = await _socketService.receiveMessage();
    _question = new Question(response.getData()[0], response.getData()[1]);

    setState(() {});
  }

  Future<void> submitAnswer(int answerId) async {
    _socketService.sendMessage(
        Message(SUBMIT_ANSWER_REQUEST_CODE, {"answerId": answerId}));
    Message response = await _socketService.receiveMessage();

    if (response.getData()[0] == answerId) {
      // navigate to right page
    } else {
      // navigte to worng page
    }
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
        body: Stack(children: [
      SingleChildScrollView(
          scrollDirection: Axis.vertical,
          child: Center(
              child: Column(children: [
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
