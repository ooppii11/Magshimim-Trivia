class Category {
  final String _name;
  final bool _permission;

  Category(this._name, this._permission);

  String getName() {
    return _name;
  }

  bool getPermission() {
    return _permission;
  }
}
