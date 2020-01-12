#include <DigitalEqualizerRemoteApplication.hpp>
#include <DigitalEqualizerRemote.hpp>

int main(int argc, char** argv) {
    DigitalEqualizerRemoteApplication app(argc, argv);
    DigitalEqualizerRemote view;
    view.startConnecting();
    view.show();
    return app.exec();
}
