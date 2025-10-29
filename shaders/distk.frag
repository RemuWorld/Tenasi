#version 330 core
    out vec4 FragColor;
    in vec3 fragPos;
    
    void main()
    {

        if((fragPos.x * fragPos.x + fragPos.y * fragPos.y) <= 0.2f)
        {
            if((sin(fragPos.x * 57.29578) <= sin(fragPos.y * 57.29578)))
            {
                FragColor = vec4(0.2f, 0.1f, 0.8f, 1.0f);
            }
            else
            {
                FragColor = vec4(0.8f, 0.2f, 0.1f, 1.0f);
            }
        }
        else
        {
            if(sin(fragPos.x * 57.29578) >= sin(fragPos.y * 57.29578))
            {
                FragColor = vec4(0.7f, 0.1f, 0.2f, 1.0f);
            }
            else
            {
                FragColor = vec4(0.6f, 0.2f, 0.3f, 1.0f);
            }
        }
        
    }