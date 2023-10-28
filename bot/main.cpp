/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairou <mkhairou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 17:26:13 by mkhairou          #+#    #+#             */
/*   Updated: 2023/10/11 18:17:07 by mkhairou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bot.hpp"

int quit = 0;

void your_signal_handler_function(int signal_number)
{
	if(signal_number == SIGINT)
		quit = 1;
}

int main(int ac, char **av)
{
	if (ac == 3)
	{
		struct sigaction sa;
		sa.sa_handler = your_signal_handler_function;
		sigaction(SIGINT, &sa, NULL);

		try{
			Bot bot(av[1], av[2]);
			while (1)
			{
				if (quit)
					bot.send_quit();
				bot.run_bot();
			}
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
			return 1;
		}
	}
	else
		std::cerr << "Usage: ./bot port" << std::endl;
	return 0;
}
