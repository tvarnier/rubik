#ifndef VISUALIZERINCLUDES_HPP
# define VISUALIZERINCLUDES_HPP

# include <string>
# include <iostream>
# include <limits>
# include <iterator>
# include <sstream>
# include <algorithm>
# include <set>
# include <unordered_map>
# include <map>
# include <array>
# include <functional>
# include <regex>
# include <array>
# include <cmath>
# include <list>
# include <fstream>
# include <iomanip>
# include <vector>

# ifdef STB_IMAGE_IMPLEMENTATION
#   define STB_IMAGE_IMPLEMENTATION
#   include "stb_image.h"
# endif

# include <glad/glad.h>
# include "../external_lib/glfw/include/GLFW/glfw3.h"

# include <glm/glm.hpp>
# include <glm/gtc/type_ptr.hpp>
# include <glm/vec3.hpp> // glm::vec3
# include <glm/vec4.hpp> // glm::vec4
# include <glm/mat4x4.hpp> // glm::mat4
# include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
# include <glm/gtc/constants.hpp> // glm::pi
# include <glm/gtc/quaternion.hpp>
# include <glm/gtx/quaternion.hpp>
# include <glm/gtx/transform.hpp>
# include <glm/gtx/string_cast.hpp>

#endif