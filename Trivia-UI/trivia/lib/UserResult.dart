class UserResult
{
  final String _username;
  final int _correctAnswersCount;
  final int _worngAnswersCount;
  final double _averageAnswerTime;

  const  UserResult(this._username, this._correctAnswersCount, this._worngAnswersCount, this._averageAnswerTime);

  String getUsername()
  {
    return _username;
  }
  int getCorrectAnswersCount()
  {
    return _correctAnswersCount;
  }
  int getWorngAnswersCount()
  {
    return _worngAnswersCount;
  }
  double getAverageAnswerTime()
  {
    return _averageAnswerTime;
  }
}