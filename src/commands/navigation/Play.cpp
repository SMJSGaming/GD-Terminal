#include "Play.hpp"

Play::Play(): Command("play", "Closes the terminal and enters a level", { "ID", "The level ID to play" }, {}, true) {}

void Play::run(TerminalCout& cout, flags_t flags) {
    const int id = Command::parseInt(flags.at("*"));
    // Since parseInt will truncate any decimal values, it's better to use the parsed value rather than the original string
    const std::string key = std::to_string(id);
    GameLevelManagerExt* manager = GameLevelManagerExt::sharedState();
    manager->m_levelDownloadDelegate = this;

    manager->downloadLevel(id, false);
}

void Play::levelDownloadFinished(GJGameLevel* level) {
    CommandExecuter::m_cout << "Level downloaded" << TerminalCout::endl << "Loading level";

    GameSoundManager::sharedState()->playBackgroundMusic(level->getAudioFileName(), 0, 1);
    CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, PlayLayer::scene(level)));

    this->m_finished = true;
    this->m_willTransition = true;
}

void Play::levelDownloadFailed(int code) {
    CommandExecuter::m_cout << "Failed to download level. Received the " << code << " error code instead";
    this->m_finished = true;
}