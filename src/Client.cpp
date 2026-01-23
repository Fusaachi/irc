/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiroux <pgiroux@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 16:44:48 by pgiroux           #+#    #+#             */
/*   Updated: 2026/01/23 14:23:45 by pgiroux          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"


Client::Client()
{
}

Client::Client(const Client &c)
{

}

Client& Client::operator=(const Client& rhs)
{
	if (this != &rhs)
		*this = rhs;
	return(*this);

}

Client::~Client()
{
}