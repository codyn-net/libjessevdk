#include "server.ih"

void Server::attach(Optimizer &optimizer) 
{
	d_data->optimizer = optimizer;
	
	/* TODO: connect signals */
}
