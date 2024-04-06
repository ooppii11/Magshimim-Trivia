class Category {
  final String _name;
  final bool _permission;
  final int _id;

  const Category(this._name, this._id, this._permission);

  String getName() {
    return _name;
  }

  int getId() {
    return _id;
  }

  bool getPermission() {
    return _permission;
  }
}
