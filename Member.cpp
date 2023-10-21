#include "Member.hpp"
#include "Client.hpp"

// Constructors
Member::Member(Client &client, bool operator_priv, bool founder_priv, bool topic_priv) :
_client(&client),
_operator_priv(operator_priv),
_founder_priv(founder_priv),
_topic_priv(topic_priv)
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

bool	Member::getOperatorPriv() const
{
	return (this->_operator_priv);
}

void    Member::setOperatorPriv(bool op)
{
	this->_operator_priv = op;
}

bool	Member::getFounderPriv() const
{
	return (this->_founder_priv);
}

void    Member::setFounderPriv(bool fo)
{
	this->_founder_priv = fo;
}

