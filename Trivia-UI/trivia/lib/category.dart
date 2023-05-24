class Category {
  String _name;
  bool _permission;

  Category(this._name, this._permission);

  String getName() {
    return _name;
  }

  bool getPermission() {
    return _permission;
  }
}
