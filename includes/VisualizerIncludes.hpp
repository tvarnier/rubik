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
# include <queue>

# ifdef STB_IMAGE_IMPLEMENTATION
#   define STB_IMAGE_IMPLEMENTATION
#   include "stb_image.h"
# endif

# include "glad/glad.h"
# include "../external_lib/glfw/include/GLFW/glfw3.h"

# include "../external_lib/glm/glm.hpp"
# include "../external_lib/glm/gtc/type_ptr.hpp"
# include "../external_lib/glm/vec3.hpp" // glm::vec3
# include "../external_lib/glm/vec4.hpp" // glm::vec4
# include "../external_lib/glm/mat4x4.hpp" // glm::mat4
# include "../external_lib/glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective
# include "../external_lib/glm/gtc/constants.hpp" // glm::pi
# include "../external_lib/glm/gtc/quaternion.hpp"
# include "../external_lib/glm/gtx/quaternion.hpp"
# include "../external_lib/glm/gtx/transform.hpp"
# include "../external_lib/glm/gtx/string_cast.hpp"

#endif