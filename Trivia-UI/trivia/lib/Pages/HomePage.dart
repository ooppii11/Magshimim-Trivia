import 'dart:async';
import 'package:trivia/category.dart';
import 'package:trivia/components/erroToast.dart';
import 'package:trivia/Pages/RoomsListPage.dart';
import 'package:trivia/Pages/UserPage.dart';
import 'package:trivia/Pages/loginPage.dart';
import 'package:trivia/Pages/leaderBoardPage.dart';
import 'package:trivia/SocketService.dart';
import 'package:flutter/material.dart';
import 'package:trivia/message.dart';
import 'package:trivia/Pages/categoriesPageLayout.dart';
import 'package:trivia/Pages/roomPage.dart';
import 'package:trivia/room.dart';
import 'dart:convert';

// ignore_for_file: prefer_const_constructors

// ignore: must_be_immutable

class HomePage extends StatefulWidget {
  final SocketService socketService;

  const HomePage({super.key, required this.socketService});

  @override
  _HomePage createState() => _HomePage(socketService);
}

class _HomePage extends State<HomePage> with SingleTickerProviderStateMixin {
  final SocketService _socketService;
  String _enteredValue = '';
  bool _isFloatingScreenOpen = false;
  late Timer _timer;
  bool _isDialogOpen = false;
  Key _categoriesPageKey = UniqueKey();
  Key _roomsPageKey = UniqueKey();
  late List<Category> _categories = [];
  late List<Room> _rooms = [];

  _HomePage(this._socketService);

  @override
  void initState() {
    getCategoriesAndRooms();
    startTimer();
    super.initState();
  }

  @override
  void dispose() {
    cancelTimer();
    super.dispose();
  }

  void startTimer() {
    const duration = Duration(seconds: 3);
    _timer = Timer.periodic(duration, (timer) {
      if (!_isDialogOpen) {
        getCategoriesAndRooms();
      }
    });
  }

  void cancelTimer() {
    _timer.cancel();
  }

  Future<void> getCategoriesAndRooms() async {
    _socketService.sendMessage(Message(GET_CATEGORIES_CODE, {}));
    Message response = await _socketService.receiveMessage();
    List<Category> categories = [];
    if (response.getCode() == GET_CATEGORIES_RESPONSE_CODE) {
      Map<String, dynamic> catgorisData = response.getData();
      if (response.getCode() == GET_CATEGORIES_RESPONSE_CODE) {
        for (var categoryString in catgorisData["publicCategories"]) {
          categories.add(Category(categoryString[1], categoryString[0], true));
        }
      }
    }

    _socketService.sendMessage(Message(GET_ROOMS_CODE, {}));
    List<Room> rooms = [];
    response = await _socketService.receiveMessage();
    if (response.getCode() == GET_ROOMS_RESPONSE_CODE) {
      List<dynamic> dynamicList = jsonDecode(response.getData()["Rooms"]);
      List<Map<String, dynamic>> roomsData =
          dynamicList.cast<Map<String, dynamic>>().toList();
      for (var roomData in roomsData) {
        rooms.add(Room(
            roomData["Id"],
            roomData["Name"],
            roomData["CategorieId"],
            roomData["MaxPlayers"],
            roomData["NumOfQuestions"],
            roomData["Time"],
            (roomData["IsActive"] == 1) ? true : false));
      }
    }
    if (mounted) {
      setState(() {
        _roomsPageKey = UniqueKey();
        _rooms = rooms;
        _categoriesPageKey = UniqueKey();
        _categories = categories;
      });
    }
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: DefaultTabController(
        length: 2,
        child: Scaffold(
          bottomNavigationBar: BottomNavigationBar(
              type: BottomNavigationBarType.fixed,
              items: [
                BottomNavigationBarItem(
                    icon: Icon(Icons.person, color: Colors.grey[600]),
                    label: ''),
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
                _timer.cancel();
                if (value == 0) {
                  Navigator.pushReplacement(
                    context,
                    MaterialPageRoute(
                      builder: (_) => UserPage(
                        socketService: _socketService,
                      ),
                    ),
                  );
                }
                if (value == 1) {
                  _openPopUp();
                }
                if (value == 2) {
                  Navigator.pushReplacement(
                      context,
                      MaterialPageRoute(
                        builder: (_) => LeaderBoardPage(
                          socketService: _socketService,
                        ),
                      ));
                }
              }),
          appBar: AppBar(
              bottom: TabBar(
                indicator: BoxDecoration(
                  borderRadius: BorderRadius.circular(
                    25.0,
                  ),
                  color: Colors.green,
                ),
                labelColor: Colors.white,
                unselectedLabelColor: Colors.black,
                tabs: const [
                  Tab(
                    icon: Icon(Icons.category),
                  ),
                  Tab(
                    text: 'Rooms',
                  ),
                ],
              ),
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
                                        socketService: _socketService,
                                      )));
                        }
                      }),
                ),
              ]),
          body: Stack(
            children: [
              TabBarView(
                children: [
                  CategoriesPage(
                    key: _categoriesPageKey, // Assign the key
                    socketService: _socketService,
                    categories: _categories,
                    disposeCallback: dispose,
                    setIsDialogOpen: (bool isOpen) {
                      setState(() {
                        _isDialogOpen = isOpen;
                      });
                    },
                  ),
                  RoomsPage(
                    key: _roomsPageKey,
                    socketService: _socketService,
                    rooms: _rooms,
                    disposeCallback: dispose,
                  )
                ],
              ),
              if (_isFloatingScreenOpen) _buildFloatingScreen(),
            ],
          ),
        ),
      ),
    );
  }

  void _openPopUp() {
    setState(() {
      _isFloatingScreenOpen = true;
    });
  }

  Widget _buildFloatingScreen() {
    return Stack(
      fit: StackFit.expand,
      children: [
        Positioned.fill(
          child: GestureDetector(
            onTap: () {
              setState(() {
                _isFloatingScreenOpen = false;
              });
            },
            child: Container(color: Colors.transparent),
          ),
        ),
        Align(
          alignment: Alignment.bottomCenter,
          child: Container(
            height: 60,
            color: Colors.grey[200],
            child: Row(
              mainAxisAlignment: MainAxisAlignment.spaceEvenly,
              children: [
                InkWell(
                  onTap: () {
                    showDialog(
                      context: context,
                      builder: (BuildContext context) {
                        return AlertDialog(
                          title: Text('Join'),
                          content: Column(
                            mainAxisSize: MainAxisSize.min,
                            children: [
                              TextField(
                                onChanged: (value) {
                                  _enteredValue = value;
                                },
                                keyboardType: TextInputType.number,
                                decoration: InputDecoration(
                                  hintText: 'Enter Room ID',
                                ),
                              ),
                              SizedBox(height: 10),
                              ElevatedButton(
                                child: Text('Join'),
                                onPressed: () {
                                  Navigator.of(context).pop();
                                  joinRoom();
                                },
                              ),
                            ],
                          ),
                        );
                      },
                    );
                    setState(() {
                      _isFloatingScreenOpen = false;
                    });
                  },
                  child: Icon(Icons.people),
                ),
                InkWell(
                  onTap: () {
                    // Handle Create icon press
                    setState(() {
                      _isFloatingScreenOpen = false;
                    });
                  },
                  child: Icon(Icons.create),
                )
              ],
            ),
          ),
        ),
      ],
    );
  }

  void joinRoom() async {
    _socketService
        .sendMessage(Message(11, {"roomId": int.parse(_enteredValue)}));
    final Message response = await _socketService.receiveMessage();
    if (response.getCode() == 10) {
      Navigator.pushReplacement(
        context,
        MaterialPageRoute(
          builder: (_) => RoomPage(
            socketService: _socketService,
            admin: false,
            roomId: int.parse(_enteredValue),
          ),
        ),
      );
    } else {
      errorToast(context, response.getData()["Error"], 2);
    }
  }
}
