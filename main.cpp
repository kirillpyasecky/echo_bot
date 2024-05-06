#include <tgbotxx/tgbotxx.hpp>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include <fstream>
#include <csignal>

using namespace tgbotxx;

class EchoBot : public Bot {
public:
    EchoBot(const std::string& token) : Bot(token) { }

private:
    void onStart() override {
      api()->deleteWebhook(true);
      spdlog::info("Bot {} started", api()->getMe()->firstName);
    }

    void onStop() override {
      spdlog::info("Bot {} stopped", api()->getMe()->firstName);
    }
    
    void onAnyMessage(const Ptr<Message>& message) override {
      if (message->text.empty()) {
        return;
      }
      spdlog::info("Received \"{0}\" from {1}", message->text, message->from->username);
      api()->sendMessage(message->chat->id, message->text); // Echo back message
    }
};

int main() {
  std::ifstream config_file("config.json");
  if (!config_file) {
    spdlog::error("Erorr opening config.json file");
    return EXIT_FAILURE;
  }
  if (config_file.peek() == std::ifstream::traits_type::eof()) {
    spdlog::error("Empty config.json file");
    return EXIT_FAILURE;
  }

  auto config = nlohmann::json::parse(config_file);
  std::string token = config["BOT_TOKEN"].get<std::string>();

  static std::unique_ptr<EchoBot> BOT(new EchoBot(token));
  std::signal(SIGINT, [](int) { // Graceful Bot exit on CTRL+C
    if(BOT) {
      spdlog::info("Stopping Bot. Please wait...");
      BOT->stop();
    }
    std::exit(EXIT_SUCCESS);
  });
  BOT->start();
  return EXIT_SUCCESS;
}
