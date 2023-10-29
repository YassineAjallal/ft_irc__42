/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 12:09:07 by mkhairou          #+#    #+#             */
/*   Updated: 2023/10/12 16:25:04 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"
#include "../Toolkit.hpp"

void Bot::join_channesl()
{
    usleep(500);
    const char *sender = "JOIN #general\r\n";
    send(this->socket_id, sender, strlen(sender), 0);
    usleep(500);
    const char *sender2 = "JOIN #random\r\n";
    send(this->socket_id, sender2, strlen(sender2), 0);
    usleep(500);
    const char *sender3 = "JOIN #mkhairou mkhairou\r\n";
    send(this->socket_id, sender3, strlen(sender3), 0);
    usleep(500);
    const char *sender4 = "JOIN #yajallal yajallal\r\n";
    send(this->socket_id, sender4, strlen(sender4), 0);
    usleep(500);
    const char *sender5 = "JOIN #hmeftah hmeftah\r\n";
    send(this->socket_id, sender5, strlen(sender5), 0);
}

Bot::Bot(const std::string &port, const std::string &pass)
{
    name = "irc_bot";
    init_jokes();
    init_facts();
    init_help();
    this->Forbidden_msg.push_back("forbidden words:");
    this->Forbidden_msg.push_back("amzgis");
    this->Forbidden_msg.push_back("yassin");
    _bzero(&this->hints, sizeof(this->hints));
    this->hints.ai_family = AF_INET;
	this->hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(NULL , port.c_str(), &this->hints, &this->res))
        throw std::runtime_error("getaddrinfo failed");
    this->socket_id = socket(this->hints.ai_family, this->hints.ai_socktype, this->hints.ai_protocol);
    if(this->socket_id == -1)
        throw std::runtime_error("socket failed");
    if (connect(this->socket_id, res->ai_addr, res->ai_addrlen))
        throw std::runtime_error("connect failed");
    std::string tmp = "CAP LS\r\nNICK irc_bot\r\nUSER irc_bot irc_bot localhost :irc_bot\r\nPASS " + pass;
    const char *msg = tmp.c_str();
    send(this->socket_id, msg, strlen(msg), 0);
    join_channesl();
}

Bot::~Bot()
{
}

void Bot::init_jokes()
{
    jokes.push_back("A taxing situation: According to unofficial sources, a new simplified income-tax form contains only four lines.");
    jokes.push_back("Timing is everything: Q: How many telemarketers does it take to change a light bulb? A: Only one, but he has to do it while you are eating dinner.");
    jokes.push_back("Just wondering: If Dracula can’t see his reflection in the mirror, how come his hair is always so neatly combed?");
    jokes.push_back("A mathematician wanders back home at 3 a.m. and proceeds to get an earful from his wife. 'You’re late!' she yells. 'You said you’d be home by 11:45!' 'Actually,' the mathematician replies coolly, 'I said I’d be home by a quarter of 12.'");
    jokes.push_back("René Descartes walks into a bar. The bartender says, 'Would you like a beer?'");
    jokes.push_back("What do the movies Titanic and The Sixth Sense have in common? Icy dead people.");
    jokes.push_back("What's the difference between a golfer and a skydiver? A golfer goes whack 'darn' and a skydiver goes 'darn' whack.");
    jokes.push_back("What do you call a woman who sets fire to all her bills? Bernadette.");
    jokes.push_back("What did the full glass say to the empty glass? 'You look drunk.'");
    jokes.push_back("Why can't you explain puns to kleptomaniacs? They always take things literally.");
    jokes.push_back("What's the difference between a hippo and a Zippo? One is really heavy, and the other is a little lighter.");
    jokes.push_back("What do Alexander the Great and Winnie the Pooh have in common? Same middle name.");
    jokes.push_back("Did you hear how the zombie bodybuilder hurt his back? He was deadlifting.");
    jokes.push_back("What do you call a Frenchman wearing sandals? Phillipe Phillope.");
    jokes.push_back("Two men meet on opposite sides of a river. One shouts to the other, 'I need you to help me get to the other side!' The other guy replies, 'You're on the other side!'");
}

void Bot::init_facts()
{
    facts.push_back("The longest time between two twins being born is 87 days.");
    facts.push_back("The world's deepest postbox is in Susami Bay in Japan. It's 10 meters underwater.");
    facts.push_back("In 2007, an American man named Corey Taylor tried to fake his own death in order to get out of his cell phone contract without paying a fee.");
    facts.push_back("In 1980, a Las Vegas hospital suspended workers for betting on when patients would die.");
    facts.push_back("An eagle can kill a young deer and fly away with it.");
    facts.push_back("Heart attacks are more likely to happen on a Monday.");
    facts.push_back("If you consistently fart for 6 years & 9 months, enough gas is produced to create the energy of an atomic bomb.");
    facts.push_back("You can't snore and dream at the same time.");
    facts.push_back("The following can be read forward and backwards: Do geese see God?");
    facts.push_back("A baby octopus is about the size of a flea when it is born.");
    facts.push_back("A sheep, a duck and a rooster were the first passengers in a hot air balloon.");
    facts.push_back("In Uganda, 50% of   the population is under 15 years of age.");
    facts.push_back("Hitler’s mother considered abortion but the doctor persuaded her to keep the baby.");
    facts.push_back("Arab women can initiate a divorce if their husbands don’t pour coffee for them.");
    facts.push_back("Recycling one glass jar saves enough energy to watch television for 3 hours.");
}

void Bot::init_help()
{
    help_message = "Usage: bot [option]\nOptions:\n \t\t\t -h,--help\t\t\tPrint this help message\n \t\t\t -j,--joke\t\t\tTell a joke\n \t\t\t -d,--date\t\t\tTell the date\n \t\t\t -f,--fact\t\t\tTell a fact\n \t\t\t -r,--roll\t\t\tRoll some dice\n \t\t\t -v,--version\t\t\tPrint the version\n";
}

void Bot::print_help()
{
    std::string tmp = buffer;
    std::stringstream ss(help_message);
    std::string temp;
    while(std::getline(ss, temp, '\n'))
    {
        buffer = tmp + temp + "\r\n";
        send(socket_id, buffer.c_str(), buffer.length(), 0);
        usleep(500);
    }
    buffer.clear();
}

void Bot::print_version()
{
    buffer += "Bot version 1.0\r\n";
}

void Bot::print_joke()
{
    srand(time(NULL));
    int joke = rand() % 15;

   buffer += jokes[joke];
   buffer += "\r\n";
}


void Bot::print_date()
{
    time_t now = time(NULL);

    char *dt = ctime(&now);
    std::string tmp = dt;
    buffer += tmp + "\r\n";
}

void Bot::print_roll()
{
    srand(time(NULL));
    int roll = rand() % 6 + 1;
    std::string tmp;
    std::stringstream ss(tmp);
    ss << roll;
    buffer += "rollin' the dice: ";
    buffer += "you rolled a ";
    buffer += ss.str();
    buffer += "\r\n";
}

void Bot::print_fact()
{
    srand(time(NULL));
    int fact = rand() % 15;

    buffer += facts[fact];
    buffer += "\r\n";
}

void Bot::bot_main(std::vector<std::string> &commands)
{
    std::string option = commands[0];
    if(option  == "")
    {
        print_help();
        return;
    }
    else if(option == "-j" || option == "--joke")
        print_joke();
    else if(option == "-d" || option == "--date")
        print_date();
    else if(option == "-f" || option == "--fact")
        print_fact();
    else if(option == "-r" || option == "--roll")
        print_roll();
    else if(option == "-v" || option == "--version")
        print_version();
    else if(option == "-h" || option == "--help")
        print_help();
    else
    {
        std::string tmp = buffer;
        buffer += "Error: Invalid option\r\n";
        send(socket_id, buffer.c_str(), buffer.length(), 0);
        buffer = tmp;
        print_help();
    }
}

void Bot::check_conversation(std::vector<std::string> &conversation)
{
    for(std::vector<std::string>::iterator it = conversation.begin(); it != conversation.end(); it++)
    {
        std::vector<std::string>::iterator i =std::find(Forbidden_msg.begin(), Forbidden_msg.end(), *it);
        if(i != Forbidden_msg.end())
        {
            buffer = "KICK "+ this->user +" " + this->sender +" :using forbidden words\r\n";
        }
    }

}

void Bot::parse_command(std::string command)
{
    std::vector<std::string> commands;
    std::stringstream ss(command);
    std::string temp;
    while(ss >> temp)
        commands.push_back(temp);
    this->sender = commands[0];
    this->sender = this->sender.substr(1, this->sender.find("!") - 1);
    this->cmd = commands[1];
    this->user = commands[2];
    std::vector<std::string>::iterator it = std::find(commands.begin(), commands.end(), ":");
    commands.erase(commands.begin(), it + 1);
    if (this->cmd == "PRIVMSG")
    {
        if(this->user == "irc_bot")
        {
            buffer = "PRIVMSG "+ this->sender +" :";
            bot_main(commands);
        }
        else if(this->user.at(0) == '#')
        {
            check_conversation(commands);
        }
    }
}

void Bot::run_bot()
{
    int status = -1;
    char buf[4096];
    status = recv(socket_id, buf, sizeof(buf), 0);
    if(status != 0)
    {
        std::string tmp = buf;
        std::stringstream ss(tmp);
        std::string temp;
        std::getline(ss, temp, '\n');
        tmp = temp;
        int i = tmp.find(" :");
        tmp.insert(i + 2, " ");
        parse_command(tmp);
        if(buffer.length() > 0)
        {
            send(socket_id, buffer.c_str(), buffer.length(), 0);
            buffer.clear();
        }
    }
    else
    {
       close(socket_id);
       throw std::runtime_error("lost connection with the server");
    }
}

void Bot::send_quit()
{
    std::string tmp = "QUIT\r\n";
    const char *msg = tmp.c_str();
    send(this->socket_id, msg, strlen(msg), 0);
    close(socket_id);
    exit(0);
}
