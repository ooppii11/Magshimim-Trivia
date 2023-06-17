import 'package:flutter/material.dart';
import 'dart:async';
import 'dart:io';
import 'dart:convert';
import 'package:trivia/SocketService.dart';

class WaitingPage extends StatefulWidget {
  final SocketService socketService;
  final int time;
  const WaitingPage({super.key, required this.socketService, required this.time});
  @override
  _WaitingPageState createState() => _WaitingPageState(socketService, time);
}

class _WaitingPageState extends State<WaitingPage> {
  late List<String> _funFacts = [];
  late bool _moveToNextPage = false;
  late Timer _apiTimer;
  final int _time;
  final SocketService _socketService;
  
  _WaitingPageState(this._socketService, this._time);

  Future<void> getFunFacts() async {
    _funFacts.clear();
    if(!_moveToNextPage)
    {
      String url = "https://api.api-ninjas.com/v1/facts?limit=5";
      HttpClient client =  HttpClient()
      ..badCertificateCallback = ((X509Certificate cert, String host, int port) => true);
      HttpClientRequest request = await client.getUrl(Uri.parse(url));
      request.headers.set('X-Api-Key', 'FhmWPU3gkVYjlnr9/tab9w==A2gqA9dgzXHcSU6I');
      HttpClientResponse response = await request.close();
      final data = await response.transform(utf8.decoder).join();
      jsonDecode(data).forEach((element) {
        _funFacts.add(element["fact"]);
      });
      client.close();
      setState(() {
      });
    }
  }

  void _startTimers() {
    _apiTimer = Timer.periodic(const Duration(seconds: 60), (timer) {
      getFunFacts();
    });
    Future.delayed(Duration(seconds: _time), () {
      _moveToNextPage = true;
      print("next page");
      /*
      Navigator.pushReplacement(
        context,
        MaterialPageRoute(
          builder: (_) => UserPage(
            socketService: widget.socketService,
          ),
        ),
      );
      */
    });
  }

  @override
  void initState() {
    super.initState();
    _startTimers();
  }

  @override
  void dispose() {
    _apiTimer?.cancel();
    super.dispose();
  }
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: Container(
        color: Colors.lightBlue,
        child: Column(
          children: [
            Container(
              height: MediaQuery.of(context).size.height * 0.25,
              width: MediaQuery.of(context).size.width,
              color: Color.fromARGB(255, 111, 156, 235),
              padding: const EdgeInsets.all(16.0),
              child: Column(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  Align(
                    alignment: Alignment.center,
                    child: const Text(
                      "Waiting for other players to finish the game...",
                      style: TextStyle(fontSize: 24, color: Colors.black),
                    ),
                  ),
                  Align(
                    alignment: Alignment.center,
                    child: const SizedBox(height: 8.0),
                  ),
                  Align(
                    alignment: Alignment.center,
                    child: Text(
                      "in the meantime, here are some fun facts:",
                      style: const TextStyle(
                          fontSize: 22,
                          fontWeight: FontWeight.bold,
                          color: Colors.black),
                    ),
                  ),
                ],
              ),
            ),
            Expanded(
              child: Container(
                width: MediaQuery.of(context).size.width,
                color: Color.fromARGB(255, 29, 45, 68),
                padding: const EdgeInsets.all(16.0),
                child: SingleChildScrollView(
                  scrollDirection: Axis.vertical,
                  child: Column(
                    children: [
                      Align(
                        alignment: Alignment.topLeft,
                        child: SingleChildScrollView(
                          scrollDirection: Axis.vertical,
                            child: Column(
                              crossAxisAlignment: CrossAxisAlignment.start,
                              children: [
                                for (var i = 0; i < _funFacts.length; i++)
                                  Padding(
                                    padding: EdgeInsets.only(bottom: 16.0),
                                    child: Container(
                                      padding: EdgeInsets.symmetric(
                                        vertical: 4.0, horizontal: 8.0),
                                      decoration: BoxDecoration(
                                      color: Color.fromARGB(255, 88, 128, 185),
                                      borderRadius: BorderRadius.circular(8.0),
                                      ),
                                      child: Text(
                                        (i+1).toString() + ". " + _funFacts[i],
                                        style: TextStyle(
                                          fontSize: 24,
                                          color: Colors.black,
                                        ),
                                      ),
                                    ),
                                  ),
                              ],
                            )
                      ),
                    ),
                    const SizedBox(height: 16.0),
                  ],
                ),
              ),
            ),
          )
        ],
        ),
      ),
    );
  }
}
