import 'dart:typed_data';
import 'dart:convert';

class Message {
  late int _code;
  late Map<String, dynamic> _data;
  //late dynamic _data;

  Message(this._code, this._data);
  Message.BytesConstructor(Uint8List rawData) {
    _code = 0;
    _data = {};

    int messageLength = 0;

    ByteData byteData = ByteData.sublistView(rawData);
    _code = byteData.getUint8(0);
    messageLength = byteData.getInt16(1, Endian.little);
    if (messageLength > 0) {
      String jsonString;
      try {
        jsonString = utf8.decode(byteData.buffer.asUint8List(4, messageLength),
            allowMalformed: true);
      } catch (e) {
        jsonString = utf8.decode(byteData.buffer.asUint8List(4, messageLength),
            allowMalformed: true);
      }
      _data = jsonDecode(jsonString);
    }
  }

  int getCode() {
    return _code;
  }

  Map<String, dynamic> getData() {
    return _data;
  }

  /*
  dynamic getData() {
    return _data;
  }
  */
  Uint8List encode() {
    Uint8List message;
    Uint8List dataLength = Uint8List(4);
    Uint8List messageCode = Uint8List(4);
    String jsonData = jsonEncode(_data);

    ByteData.view(messageCode.buffer).setUint32(0, _code, Endian.little);
    ByteData.view(dataLength.buffer)
        .setUint32(0, jsonData.length, Endian.little);

    message = Uint8List.fromList(
        [messageCode[0], ...dataLength, ...jsonData.codeUnits]);
    return message;
  }
}
