#ifndef MEMBER_HPP
#define MEMBER_HPP

#include <iostream>
#include <string>

class Client;

class Member {
public:
    Member(Client &client, bool operator_prev, bool founder_prev, bool topic_prev);
    ~Member();
	bool	operator==(const Client& client);
	bool	operator!=(const Client& client);
	Client* getClient() const;

	bool	getOperatorPrev() const;
	void    setOperatorPrev(bool op);

	bool	getFounderPrev() const;
	void    setFounderPrev(bool fo);

	bool	getTopicPrev() const;
	void    setTopicPrev(bool to);

private:
	Client*	_client;
	bool	_operator_prev;
	bool	_founder_prev;
	bool	_topic_prev;
};

#endif // Member_HPP
