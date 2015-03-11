Whatsapp-Parser
===============

Parses a Whatsapp conversation log and lists the number of messages sent by each person.

Sample usage:

> parser conversation.txt -a -k hello good -m -s

Messages containing hello:
Person 1 : 10
Person 3 : 5

Messages containing good:
Person 2 : 17
Person 4 : 2

Total messages:
Person 1 : 150
Person 4 : 145
Person 3 : 100
Person 2 : 70

parser [filename] [OPTION]...

-a, --all
        parses every message in the conversation log

-k, --keyword [KEYWORD]...
        parses the messages that contain the keyword only

-m, --media
        parses messages that contain media (i.e. photos)

-s, --sort
        sorts the results by message count in descending order
