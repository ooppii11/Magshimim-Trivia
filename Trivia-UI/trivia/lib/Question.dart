class Question {
  final String question;
  final Map<int, String> answers;

  Question(this.question, this.answers);

  String getQuestion() {
    return this.question;
  }

  Map<int, String> getAnswers() {
    return this.answers;
  }
}
