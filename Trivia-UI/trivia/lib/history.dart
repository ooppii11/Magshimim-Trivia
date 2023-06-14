class History {
  final String _categoryName;
  final int _categoryId;
  final int _userRank;
  final int _correctAnswers;
  final int _totalAnswers;
  final double _averageTime;
  final DateTime _CreationDate;


  History(this._categoryName, this._categoryId, this._userRank, this._correctAnswers, this._totalAnswers, this._averageTime, this._CreationDate);

  String getCategoryName() {
    return _categoryName;
  }

  int getCategoryId() {
    return _categoryId;
  }

  int getUserRank() {
    return _userRank;
  }

  int getCorrectAnswers() {
    return _correctAnswers;
  }

  int getTotalAnswers() {
    return _totalAnswers;
  }

  double getAverageTime() {
    return _averageTime;
  }

  DateTime getCreationDate() {
    return _CreationDate;
  }
  
}