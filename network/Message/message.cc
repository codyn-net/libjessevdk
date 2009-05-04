#include "message.ih"

Message::Message(Properties const &properties) 
{
	stringstream s;
	
	vector<string> props = properties.properties();
	vector<string>::iterator iter;

	for (iter = props.begin(); iter != props.end(); ++iter)
	{
		string value = properties.property(*iter);
		
		s << value << " " << value.length() << " " << value << ";";
	}
	
	d_data = new Data();
	addPrivateData(&d_data);

	d_data->serialized = s.str();
}
