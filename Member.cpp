#include "Member.hpp"
#include "Client.hpp"

// Constructors
Member::Member(Client &client, bool operator_prev, bool founder_prev, bool topic_prev) :
_client(&client),
_operator_prev(operator_prev),
_founder_prev(founder_prev),
_topic_prev(topic_prev)
{}
Member::~Member(){}

bool Member::operator==(const Client& client)
{
	return (this->_client->getSockID() == client.getSockID());
}

Client* Member::getClient() const
{
	return (this->_client);
}

bool Member::operator!=(const Client& client)
{
	return (this->_client->getSockID() != client.getSockID());
}

bool	Member::getOperatorPrev() const
{
	return (this->_operator_prev);
}

void    Member::setOperatorPrev(bool op)
{
	this->_operator_prev = op;
}

bool	Member::getFounderPrev() const
{
	return (this->_founder_prev);
}

void    Member::setFounderPrev(bool fo)
{
	this->_founder_prev = fo;
}
bool	Member::getTopicPrev() const
{
	return (this->_topic_prev);
}

void    Member::setTopicPrev(bool to)
{
	this->_topic_prev = to;
}
