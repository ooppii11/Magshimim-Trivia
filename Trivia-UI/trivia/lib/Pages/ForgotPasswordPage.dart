import 'basePage.dart';
import 'package:trivia/SocketService.dart';

class ForgotPasswordPage extends BasePage {
  const ForgotPasswordPage({super.key, 
    required SocketService socketService,
  }) : super(socketService: socketService);
}
