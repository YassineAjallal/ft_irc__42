#ifndef MEMBER_HPP
#define MEMBER_HPP

#include <iostream>
#include <string>

class Client;

class Member {
public:
    Member(Client &client, bool operator_priv, bool founder_priv, bool topic_priv);
    ~Member();
	bool	operator==(const Client& client);
	bool	operator!=(const Client& client);
	Client* getClient() const;

	bool	getOperatorPriv() const;
	void    setOperatorPriv(bool op);

	bool	getFounderPriv() const;
	void    setFounderPriv(bool fo);

private:
	Client*	_client;
	bool	_operator_priv;
	bool	_founder_priv;
};

#endif // Member_HPP
