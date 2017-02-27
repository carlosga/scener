#ifndef SCENER_CONTENT_GLTF_CONSTANTS_HPP
#define SCENER_CONTENT_GLTF_CONSTANTS_HPP

#include <string>

namespace scener::content::gltf
{
    const std::string k_accessors = "accessors";
    const std::string k_animation = "animation";
    const std::string k_aspect_ratio = "aspectRatio";
    const std::string k_asset = "asset";
    const std::string k_attributes = "attributes";
    const std::string k_bind_shape_matrix = "bindShapeMatrix";
    const std::string k_buffer = "buffer";
    const std::string k_buffer_view = "bufferView";
    const std::string k_buffer_views = "bufferViews";
    const std::string k_byte_offset = "byteOffset";
    const std::string k_byte_stride = "byteStride";
    const std::string k_byte_length = "byteLength";
    const std::string k_camera = "camera";
    const std::string k_channels = "channels";
    const std::string k_children = "children";
    const std::string k_component_type = "componentType";
    const std::string k_count = "count";
    const std::string k_double_sided = "doubleSided";
    const std::string k_extensions = "extensions";
    const std::string k_extensions_used = "extensionsUsed";
    const std::string k_geometry = "geometry";
    const std::string k_id = "id";
    const std::string k_image = "image";
    const std::string k_images = "images";
    const std::string k_indices = "indices";
    const std::string k_inverse_bind_matrices = "inverseBindMatrices";
    const std::string k_joint_name = "jointName";
    const std::string k_joint_names = "jointNames";
    const std::string k_light = "light";
    const std::string k_lights = "lights";
    const std::string k_material = "material";
    const std::string k_materials = "materials";
    const std::string k_max = "max";
    const std::string k_meshes = "meshes";
    const std::string k_min = "min";
    const std::string k_mode = "mode";
    const std::string k_name = "name";
    const std::string k_node = "node";
    const std::string k_nodes = "nodes";
    const std::string k_parameters = "parameters";
    const std::string k_path = "path";
    const std::string k_premultiplied_alpha = "premultipliedAlpha";
    const std::string k_primitive = "primitive";
    const std::string k_primitives = "primitives";
    const std::string k_profile = "profile";
    const std::string k_program = "program";
    const std::string k_sampler = "sampler";
    const std::string k_samplers = "samplers";
    const std::string k_scene = "scene";
    const std::string k_scenes = "scenes";
    const std::string k_semantic = "semantic";
    const std::string k_skin = "skin";
    const std::string k_skins = "skins";
    const std::string k_source = "source";
    const std::string k_sources = "sources";
    const std::string k_target = "target";
    const std::string k_technique = "technique";
    const std::string k_time = "TIME";
    const std::string k_type = "type";
    const std::string k_uniforms = "uniforms";    
    const std::string k_uri = "uri";    
    const std::string k_values = "values";
    const std::string k_value = "value";
    const std::string k_version = "version";

    const std::string k_matrix      = "matrix";
    const std::string k_rotation    = "rotation";
    const std::string k_scale       = "scale";
    const std::string k_translation = "translation";

    const std::string k_vertex_shader   = "vertexShader";
    const std::string k_fragment_shader = "fragmentShader";

    const std::string k_mag_filter  = "magFilter";
    const std::string k_min_filter  = "minFilter";
    const std::string k_wrap_s      = "wrapS";
    const std::string k_wrap_t      = "wrapT";

    const std::string k_scalar = "SCALAR";
    const std::string k_vec2   = "VEC2";
    const std::string k_vec3   = "VEC3";
    const std::string k_vec4   = "VEC4";
    const std::string k_mat2   = "MAT2";
    const std::string k_mat3   = "MAT3";
    const std::string k_mat4   = "MAT4";

    const std::string k_joint        = "JOINT";
    const std::string k_normal       = "NORMAL";
    const std::string k_position     = "POSITION";
    const std::string k_textbinormal = "TEXBINORMAL";
    const std::string k_textcoord_0  = "TEXCOORD_0";
    const std::string k_texttangent  = "TEXTANGENT";
    const std::string k_weight       = "WEIGHT";

    const std::string k_model                        = "MODEL";
    const std::string k_model_inverse                = "MODELINVERSE";
    const std::string k_model_inverse_transpose      = "MODELINVERSETRANSPOSE";
    const std::string k_model_view                   = "MODELVIEW";
    const std::string k_model_view_inverse_transpose = "MODELVIEWINVERSETRANSPOSE";
    const std::string k_model_view_inverse           = "MODELVIEWINVERSE";
    const std::string k_model_view_projection        = "MODELVIEWPROJECTION";
    const std::string k_model_view_projection_inverse= "MODELVIEWPROJECTIONINVERSE";
    const std::string k_view                         = "VIEW";
    const std::string k_view_inverse                 = "VIEWINVERSE";
    const std::string k_projection                   = "PROJECTION";
    const std::string k_projection_inverse           = "PROJECTIONINVERSE";
    const std::string k_joint_matrix                 = "JOINTMATRIX";   
}

#endif // SCENER_CONTENT_GLTF_CONSTANTS_HPP
