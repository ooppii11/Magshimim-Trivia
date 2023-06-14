import 'package:trivia/components/erroToast.dart';
import 'package:trivia/SocketService.dart';
import 'package:flutter/material.dart';
import 'package:trivia/room.dart';
import 'package:trivia/message.dart';
import 'package:trivia/Pages/RoomPage.dart';

int GET_ROOMS_CODE = 4;
int JOIN_ROOM_REQUEST_CODE = 11;
int ERROR_CODE = 99;

class RoomsPage extends StatefulWidget {
  final SocketService socketService;
  final List<Room> rooms;

  const RoomsPage({
    Key? key,
    required this.socketService,
    required this.rooms,
  }) : super(key: key);

  @override
  _RoomsPage createState() => _RoomsPage(socketService, rooms);
}

class _RoomsPage extends State<RoomsPage> {
  final SocketService _socketService;
  final List<Room> _rooms;

  _RoomsPage(this._socketService, this._rooms);

  void joinRoom(Room room) async {
    _socketService.sendMessage(Message(11, {"roomId": room.getId()}));
    final Message response = await _socketService.receiveMessage();
    if (response.getCode() == 10) {
      Navigator.pushReplacement(
        context,
        MaterialPageRoute(
          builder: (_) => RoomPage(
            socketService: widget.socketService,
            admin: false,
            roomId: room.getId(),
            //pass the room id
          ),
        ),
      );
    } else {
      errorToast(context, response.getData()[0], 2);
    }
  }

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
                            style: const TextStyle(
                                color: Colors.white, fontSize: 25),
                          ),
                        ),
                      ]))))
    ]));
  }
}
