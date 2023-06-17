class Question {
  final String question;
  final Map<int, String> answers;

  Question(this.question, this.answers);

  String getQuestion() {
    return question;
  }

  Map<int, String> getAnswers() {
    return answers;
  }
}
