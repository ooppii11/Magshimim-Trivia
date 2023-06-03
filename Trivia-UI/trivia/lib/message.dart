import 'dart:typed_data';
import 'dart:convert';

class Message {
  late int _code;
  late Map<String, dynamic> _data;

  Message(this._code, this._data);
  Message.BytesConstructor(Uint8List rawData) {
    this._code = 0;
    this._data = {};

    int messageLength = 0;

    ByteData byteData = ByteData.sublistView(rawData);
    _code = byteData.getUint8(0);
    messageLength = byteData.getInt16(1, Endian.little);
    if (messageLength > 0) {
      String jsonString = "";

      for (int i = 4; i < messageLength + 4; i++) {
        jsonString += String.fromCharCode(byteData.buffer.asInt8List()[i]);
      }
      this._data = jsonDecode(jsonString);
    }
  }

  int getCode() {
    return _code;
  }

  Map<String, dynamic> getData() {
    return _data;
  }

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
