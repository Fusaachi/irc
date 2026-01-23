/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiroux <pgiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:44:45 by pgiroux           #+#    #+#             */
/*   Updated: 2026/01/23 14:23:53 by pgiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
class Client
{
private:
	std::string _nickname;
	std::string _username;
public:
	Client();
	Client(const Client &c);
	Client &operator=(const Client &rhs);
	~Client();
};


