class History {
  final String _categoryName;
  final int _score;

  History(this._categoryName, this._score);

  String getCategoryName() {
    return _categoryName;
  }

  int getScore() {
    return _score;
  }
}