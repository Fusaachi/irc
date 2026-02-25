/* This project has been created as part of the 42 curriculum by <zmurie>, <pgiroux>, <pfranke>

## Description

	Internet Relay Chat or IRC is a text-based communication protocol on the Internet.
	It offers real-time messaging that can be either public or private. Users can exchange direct messages and join group channels.
	IRC clients connect to IRC servers in order to join channels. IRC servers are connected together to form a network.

	The server forms the backbone of IRC, providing a point to which clients may connect to to talk to each other, and a point for other servers to connect to, forming a IRC network.  
	The only network configuration allowed for IRC servers is that of a spanning tree where each server acts as a central node for the rest of the net it sees.

## Instructions

	1) At the source of the file, open a terminal and make 

	2) Server side

		./ircserv [PORT] [PASSWORD]

	3) Client side 

		nc -C localhost [PORT]

		4) Register with the COMMANDS
			PASS <PASSWORD>
			USER <username>
			NICK <nickname>

		5) COMMANDS :

			Command: 		JOIN 
			Parameters: 	<#channel>

			The JOIN command is used by client to start listening a specific channel.


			Command:		PART
			Parameters: 	<#channel>

			The PART message causes the client sending the message to be removed from the list of active users for all given channels listed in the parameter string.


			Command:		QUIT
			Parameters:		[<quit message>]

			A client session is ended with a quit message.  
			The server must close the connection to a client which sends a QUIT message. 
			If a "Quit Message" is given, this will be sent instead of the default message, the nickname.


			Command:		MODE
			Parameters:		<#channel> {[+|-]|i|t|k|o|l}

			The MODE command is a dual-purpose command in IRC.  
			It allows both usernames and channels to have their mode changed.  
			The rationale for this choice is that one day nicknames will be obsolete and the equivalent property will be the channel.
			When parsing MODE messages, it is recommended that the entire message be parsed first and then the changes which resulted then passed on.

			The MODE command is provided so that channel operators may change the characteristics of `their' channel.  
			It is also required that servers be able to change channel modes so that channel operators may be created.

   			The various modes available for channels are as follows:

				i - invite-only channel flag;
				t - topic settable by channel operator only flag;
				o - give/take channel operator privileges;
				k - set a channel key (password).
				l - set the user limit to channel;


			Command:		TOPIC
			Parameters:		<#channel> <topic>

			The TOPIC message is used to change or view the topic of a channel.
   			The topic for channel <channel> is returned if there is no <topic> given.  
			If the <topic> parameter is present, the topic for that channel will be changed, if the channel modes permit this action.


			Command:		INVITE
			Parameters:		<nickname> <#channel> 

			The INVITE message is used to invite users to a channel.  
			The parameter <nickname> is the nickname of the person to be invited to the target channel <channel>.  
			There is no requirement that the channel the target user is being invited to must exist or be a valid channel.  
			To invite a user to a channel which is invite only (MODE +i), the client sending the invite must be recognised as being a channel operator on the given channel.


      		Command: 		KICK
   			Parameters: 	<#channel> <user> [<comment>]

   			The KICK command can be  used  to  forcibly  remove  a  user  from  a channel.   
			It 'kicks them out' of the channel (forced PART).


			Command:		PRIVMSG
			Parameters:		<receiver> : <text to be send>

			PRIVMSG is used to send private messages between users. 
			<receiver> is the nickname of the receiver of the message.  
			<receiver> can also be a list of names or channels separated with commas.


			Command:		PING
   			Parameters: 	<server> 

			The PING message is used to test the presence of an active client at the other end of the connection.  
			A PING message is sent at regular intervals if no other activity detected coming from a connection.  
			If a connection fails to respond to a PING command within a set amount of time, that connection is closed.
			Any client which receives a PING message must respond to <server> (server which sent the PING message out) as quickly as possible with an appropriate PONG message to indicate it is still there and alive.

## Resources 
	https://datatracker.ietf.org/doc/html/rfc1459#page-25
	https://www.codequoi.com/programmation-reseau-via-socket-en-c/
	https://medium.com/@afatir.ahmedfatir/small-irc-server-ft-irc-42-network-7cee848de6f9
	https://medium.com/@mohcin.ghalmi/irc-server-internet-relay-chat-bd08e4f469f8