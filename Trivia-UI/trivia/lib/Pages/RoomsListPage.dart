import 'package:trivia/SocketService.dart';
import 'package:flutter/material.dart';
import 'package:trivia/room.dart';
import 'package:trivia/message.dart';

int GET_ROOMS_CODE = 4;
int JOIN_ROOM_REQUEST_CODE = 11;
int ERROR_CODE = 99;

class RoomsPage extends StatefulWidget {
  final SocketService socketService;

  const RoomsPage({super.key, required this.socketService});

  @override
  _RoomsPage createState() => _RoomsPage(socketService);
}

class _RoomsPage extends State<RoomsPage> {
  final SocketService _socketService;
  final List<Room> _rooms = [];

  _RoomsPage(this._socketService);

  Future<void> getRooms() async {
    _socketService.sendMessage(Message(GET_ROOMS_CODE, {}));
    final Message response = await _socketService.receiveMessage();

    Map<String, dynamic> data = response.getData();
    for (var roomData in data["Rooms"]) {
      _rooms.add(Room(roomData[0], roomData[1], roomData[2], roomData[3],
          roomData[4], roomData[5], roomData[6]));
    }
  }

  @override
  void initState() {
    getRooms().then((result) {
      setState(() {});
    });
  }

  Future<bool> joinRoom(Room room) async {return true;}

  @override
  Widget build(BuildContext context) {
    return SingleChildScrollView(
        child: Column(children: [
      for (Room room in _rooms)
        if (room.isActive == false)
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
                        joinRoom(room);
                      },
                      child: Column(children: [
                        Padding(
                          padding: const EdgeInsets.all(0.0),
                          child: Text(
                            room.getId().toString(),
                            style: TextStyle(color: Colors.white, fontSize: 25),
                          ),
                        ),
                      ]))))
    ]));
  }
}
