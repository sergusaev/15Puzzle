#include <connectionargumentsparser.h>

namespace net
{
QString ConnectionArgumentsParser::hostArgument() const
{
    return m_hostArgument;
}

QString ConnectionArgumentsParser::portArgument() const
{
    return m_portArgument;
}

ConnectionArgumentsParser::ConnectionArgumentsParser(const QCoreApplication &app)
{
    QString hostParameter {"server-host"};
    QString portParameter {"server-port"};
    m_parser.setApplicationDescription("15Puzzle application");
    m_parser.addHelpOption();
    m_parser.addOptions({{hostParameter, "Server AP address or a hostname.", "host", "192.168.1.69"},
                         {portParameter, "Server port", "port", "8060"}
                        });
    m_parser.process(app);

    m_hostArgument = m_parser.value(hostParameter);
    m_portArgument = m_parser.value(portParameter);
}
}
