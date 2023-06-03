class User {
  final String _username;
  final int _score;

  User(this._username, this._score);

  String getUsername() {
    return _username;
  }

  int getScore() {
    return _score;
  }

  static User fromMap(Map<String, int?> map) {
    return User((map['username'] ?? '').toString(), map['score'] ?? 0);
  }
}
