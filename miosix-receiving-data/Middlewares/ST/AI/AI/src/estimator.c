/**
  ******************************************************************************
  * @file    estimator.c
  * @author  AST Embedded Analytics Research Platform
  * @date    Sat Jun 22 15:43:51 2019
  * @brief   AI Tool Automatic Code Generator for Embedded NN computing
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2018 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */



#include "Middlewares/ST/AI/AI/include/estimator.h"

#include "Middlewares/ST/AI/AI/include/ai_platform_interface.h"
#include "Middlewares/ST/AI/AI/include/ai_math_helpers.h"

#include "Middlewares/ST/AI/AI/include/core_common.h"
#include "Middlewares/ST/AI/AI/include/layers.h"

#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#define AI_TOOLS_VERSION_MAJOR 3
#define AI_TOOLS_VERSION_MINOR 3
#define AI_TOOLS_VERSION_MICRO 0

#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#define AI_TOOLS_API_VERSION_MAJOR 1
#define AI_TOOLS_API_VERSION_MINOR 1
#define AI_TOOLS_API_VERSION_MICRO 0

#undef AI_NET_OBJ_INSTANCE
#define AI_NET_OBJ_INSTANCE g_estimator
 
#undef AI_ESTIMATOR_MODEL_SIGNATURE
#define AI_ESTIMATOR_MODEL_SIGNATURE     "8c77126d38c4898b3f26976a454be0ad"

#ifndef AI_TOOLS_REVISION_ID
#define AI_TOOLS_REVISION_ID     "(rev-)"
#endif

#undef AI_TOOLS_DATE_TIME
#define AI_TOOLS_DATE_TIME   "Sat Jun 22 15:43:51 2019"

#undef AI_TOOLS_COMPILE_TIME
#define AI_TOOLS_COMPILE_TIME    __DATE__ " " __TIME__

#undef AI_ESTIMATOR_N_BATCHES
#define AI_ESTIMATOR_N_BATCHES         (1)

/**  Forward network declaration section  *************************************/
AI_STATIC ai_network AI_NET_OBJ_INSTANCE;


/**  Forward network arrays declarations  *************************************/
AI_STATIC ai_array input_0_output_array;   /* Array #0 */
AI_STATIC ai_array dense_125_output_array;   /* Array #1 */
AI_STATIC ai_array dense_125_nl_output_array;   /* Array #2 */
AI_STATIC ai_array dense_126_output_array;   /* Array #3 */
AI_STATIC ai_array dense_126_nl_output_array;   /* Array #4 */
AI_STATIC ai_array dense_127_output_array;   /* Array #5 */
AI_STATIC ai_array dense_127_nl_output_array;   /* Array #6 */
AI_STATIC ai_array dense_128_output_array;   /* Array #7 */
AI_STATIC ai_array dense_128_nl_output_array;   /* Array #8 */


/**  Forward network tensors declarations  ************************************/
AI_STATIC ai_tensor input_0_output;   /* Tensor #0 */
AI_STATIC ai_tensor dense_125_output;   /* Tensor #1 */
AI_STATIC ai_tensor dense_125_nl_output;   /* Tensor #2 */
AI_STATIC ai_tensor dense_126_output;   /* Tensor #3 */
AI_STATIC ai_tensor dense_126_nl_output;   /* Tensor #4 */
AI_STATIC ai_tensor dense_127_output;   /* Tensor #5 */
AI_STATIC ai_tensor dense_127_nl_output;   /* Tensor #6 */
AI_STATIC ai_tensor dense_128_output;   /* Tensor #7 */
AI_STATIC ai_tensor dense_128_nl_output;   /* Tensor #8 */


/**  Forward network tensor chain declarations  *******************************/
AI_STATIC_CONST ai_tensor_chain dense_125_chain;   /* Chain #0 */
AI_STATIC_CONST ai_tensor_chain dense_125_nl_chain;   /* Chain #1 */
AI_STATIC_CONST ai_tensor_chain dense_126_chain;   /* Chain #2 */
AI_STATIC_CONST ai_tensor_chain dense_126_nl_chain;   /* Chain #3 */
AI_STATIC_CONST ai_tensor_chain dense_127_chain;   /* Chain #4 */
AI_STATIC_CONST ai_tensor_chain dense_127_nl_chain;   /* Chain #5 */
AI_STATIC_CONST ai_tensor_chain dense_128_chain;   /* Chain #6 */
AI_STATIC_CONST ai_tensor_chain dense_128_nl_chain;   /* Chain #7 */


/**  Subgraph network operators tensor chain declarations  *********************************/


/**  Subgraph network operators declarations  *********************************/


/**  Forward network layers declarations  *************************************/
AI_STATIC ai_layer_dense dense_125_layer; /* Layer #0 */
AI_STATIC ai_layer_nl dense_125_nl_layer; /* Layer #1 */
AI_STATIC ai_layer_dense dense_126_layer; /* Layer #2 */
AI_STATIC ai_layer_nl dense_126_nl_layer; /* Layer #3 */
AI_STATIC ai_layer_dense dense_127_layer; /* Layer #4 */
AI_STATIC ai_layer_nl dense_127_nl_layer; /* Layer #5 */
AI_STATIC ai_layer_dense dense_128_layer; /* Layer #6 */
AI_STATIC ai_layer_sm dense_128_nl_layer; /* Layer #7 */


/**  Arrays declarations section  *********************************************/
AI_ARRAY_OBJ_DECLARE(
  input_0_output_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 200,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  dense_125_output_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 35,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  dense_125_nl_output_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 35,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  dense_126_output_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 35,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  dense_126_nl_output_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 35,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  dense_127_output_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 35,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  dense_127_nl_output_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 35,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  dense_128_output_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 2,
  AI_STATIC)
AI_ARRAY_OBJ_DECLARE(
  dense_128_nl_output_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 2,
  AI_STATIC)


/**  Activations tensors declaration section  *********************************/
AI_TENSOR_OBJ_DECLARE(
  input_0_output,
  AI_SHAPE_INIT(1, 1, 200, 1),
  AI_STRIDE_INIT(800, 800, 4, 4),
  &input_0_output_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  dense_125_output,
  AI_SHAPE_INIT(1, 1, 35, 1),
  AI_STRIDE_INIT(140, 140, 4, 4),
  &dense_125_output_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  dense_125_nl_output,
  AI_SHAPE_INIT(1, 1, 35, 1),
  AI_STRIDE_INIT(140, 140, 4, 4),
  &dense_125_nl_output_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  dense_126_output,
  AI_SHAPE_INIT(1, 1, 35, 1),
  AI_STRIDE_INIT(140, 140, 4, 4),
  &dense_126_output_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  dense_126_nl_output,
  AI_SHAPE_INIT(1, 1, 35, 1),
  AI_STRIDE_INIT(140, 140, 4, 4),
  &dense_126_nl_output_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  dense_127_output,
  AI_SHAPE_INIT(1, 1, 35, 1),
  AI_STRIDE_INIT(140, 140, 4, 4),
  &dense_127_output_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  dense_127_nl_output,
  AI_SHAPE_INIT(1, 1, 35, 1),
  AI_STRIDE_INIT(140, 140, 4, 4),
  &dense_127_nl_output_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  dense_128_output,
  AI_SHAPE_INIT(1, 1, 2, 1),
  AI_STRIDE_INIT(8, 8, 4, 4),
  &dense_128_output_array,
  AI_STATIC)
AI_TENSOR_OBJ_DECLARE(
  dense_128_nl_output,
  AI_SHAPE_INIT(1, 1, 2, 1),
  AI_STRIDE_INIT(8, 8, 4, 4),
  &dense_128_nl_output_array,
  AI_STATIC)





/* Layer #0: "dense_125" (Dense) */
  

/* Weight tensor #1 */
AI_ARRAY_OBJ_DECLARE(
  dense_125_weights_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 7000,
  AI_STATIC)

AI_TENSOR_OBJ_DECLARE(
  dense_125_weights,
  AI_SHAPE_INIT(1, 1, 35, 200),
  AI_STRIDE_INIT(28000, 28000, 800, 4),
  &dense_125_weights_array,
  AI_STATIC)

/* Weight tensor #2 */
AI_ARRAY_OBJ_DECLARE(
  dense_125_bias_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 35,
  AI_STATIC)

AI_TENSOR_OBJ_DECLARE(
  dense_125_bias,
  AI_SHAPE_INIT(1, 1, 35, 1),
  AI_STRIDE_INIT(140, 140, 4, 4),
  &dense_125_bias_array,
  AI_STATIC)


AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_125_chain, AI_STATIC_CONST, 
  AI_TENSOR_LIST_ENTRY(&input_0_output),
  AI_TENSOR_LIST_ENTRY(&dense_125_output),
  AI_TENSOR_LIST_ENTRY(&dense_125_weights, &dense_125_bias),
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_125_layer, 0,
  DENSE_TYPE,
  dense, forward_dense,
  &AI_NET_OBJ_INSTANCE, &dense_125_nl_layer, AI_STATIC,
  .tensors = &dense_125_chain, 
)

/* Layer #1: "dense_125_nl" (Nonlinearity) */
  


AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_125_nl_chain, AI_STATIC_CONST, 
  AI_TENSOR_LIST_ENTRY(&dense_125_output),
  AI_TENSOR_LIST_ENTRY(&dense_125_nl_output),
  AI_TENSOR_LIST_EMPTY,
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_125_nl_layer, 0,
  NL_TYPE,
  nl, forward_tanh,
  &AI_NET_OBJ_INSTANCE, &dense_126_layer, AI_STATIC,
  .tensors = &dense_125_nl_chain, 
)

/* Layer #2: "dense_126" (Dense) */
  

/* Weight tensor #1 */
AI_ARRAY_OBJ_DECLARE(
  dense_126_weights_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 1225,
  AI_STATIC)

AI_TENSOR_OBJ_DECLARE(
  dense_126_weights,
  AI_SHAPE_INIT(1, 1, 35, 35),
  AI_STRIDE_INIT(4900, 4900, 140, 4),
  &dense_126_weights_array,
  AI_STATIC)

/* Weight tensor #2 */
AI_ARRAY_OBJ_DECLARE(
  dense_126_bias_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 35,
  AI_STATIC)

AI_TENSOR_OBJ_DECLARE(
  dense_126_bias,
  AI_SHAPE_INIT(1, 1, 35, 1),
  AI_STRIDE_INIT(140, 140, 4, 4),
  &dense_126_bias_array,
  AI_STATIC)


AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_126_chain, AI_STATIC_CONST, 
  AI_TENSOR_LIST_ENTRY(&dense_125_nl_output),
  AI_TENSOR_LIST_ENTRY(&dense_126_output),
  AI_TENSOR_LIST_ENTRY(&dense_126_weights, &dense_126_bias),
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_126_layer, 1,
  DENSE_TYPE,
  dense, forward_dense,
  &AI_NET_OBJ_INSTANCE, &dense_126_nl_layer, AI_STATIC,
  .tensors = &dense_126_chain, 
)

/* Layer #3: "dense_126_nl" (Nonlinearity) */
  


AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_126_nl_chain, AI_STATIC_CONST, 
  AI_TENSOR_LIST_ENTRY(&dense_126_output),
  AI_TENSOR_LIST_ENTRY(&dense_126_nl_output),
  AI_TENSOR_LIST_EMPTY,
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_126_nl_layer, 1,
  NL_TYPE,
  nl, forward_tanh,
  &AI_NET_OBJ_INSTANCE, &dense_127_layer, AI_STATIC,
  .tensors = &dense_126_nl_chain, 
)

/* Layer #4: "dense_127" (Dense) */
  

/* Weight tensor #1 */
AI_ARRAY_OBJ_DECLARE(
  dense_127_weights_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 1225,
  AI_STATIC)

AI_TENSOR_OBJ_DECLARE(
  dense_127_weights,
  AI_SHAPE_INIT(1, 1, 35, 35),
  AI_STRIDE_INIT(4900, 4900, 140, 4),
  &dense_127_weights_array,
  AI_STATIC)

/* Weight tensor #2 */
AI_ARRAY_OBJ_DECLARE(
  dense_127_bias_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 35,
  AI_STATIC)

AI_TENSOR_OBJ_DECLARE(
  dense_127_bias,
  AI_SHAPE_INIT(1, 1, 35, 1),
  AI_STRIDE_INIT(140, 140, 4, 4),
  &dense_127_bias_array,
  AI_STATIC)


AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_127_chain, AI_STATIC_CONST, 
  AI_TENSOR_LIST_ENTRY(&dense_126_nl_output),
  AI_TENSOR_LIST_ENTRY(&dense_127_output),
  AI_TENSOR_LIST_ENTRY(&dense_127_weights, &dense_127_bias),
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_127_layer, 2,
  DENSE_TYPE,
  dense, forward_dense,
  &AI_NET_OBJ_INSTANCE, &dense_127_nl_layer, AI_STATIC,
  .tensors = &dense_127_chain, 
)

/* Layer #5: "dense_127_nl" (Nonlinearity) */
  


AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_127_nl_chain, AI_STATIC_CONST, 
  AI_TENSOR_LIST_ENTRY(&dense_127_output),
  AI_TENSOR_LIST_ENTRY(&dense_127_nl_output),
  AI_TENSOR_LIST_EMPTY,
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_127_nl_layer, 2,
  NL_TYPE,
  nl, forward_tanh,
  &AI_NET_OBJ_INSTANCE, &dense_128_layer, AI_STATIC,
  .tensors = &dense_127_nl_chain, 
)

/* Layer #6: "dense_128" (Dense) */
  

/* Weight tensor #1 */
AI_ARRAY_OBJ_DECLARE(
  dense_128_weights_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 70,
  AI_STATIC)

AI_TENSOR_OBJ_DECLARE(
  dense_128_weights,
  AI_SHAPE_INIT(1, 1, 2, 35),
  AI_STRIDE_INIT(280, 280, 140, 4),
  &dense_128_weights_array,
  AI_STATIC)

/* Weight tensor #2 */
AI_ARRAY_OBJ_DECLARE(
  dense_128_bias_array, AI_DATA_FORMAT_FLOAT, 
  NULL, NULL, 2,
  AI_STATIC)

AI_TENSOR_OBJ_DECLARE(
  dense_128_bias,
  AI_SHAPE_INIT(1, 1, 2, 1),
  AI_STRIDE_INIT(8, 8, 4, 4),
  &dense_128_bias_array,
  AI_STATIC)


AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_128_chain, AI_STATIC_CONST, 
  AI_TENSOR_LIST_ENTRY(&dense_127_nl_output),
  AI_TENSOR_LIST_ENTRY(&dense_128_output),
  AI_TENSOR_LIST_ENTRY(&dense_128_weights, &dense_128_bias),
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_128_layer, 3,
  DENSE_TYPE,
  dense, forward_dense,
  &AI_NET_OBJ_INSTANCE, &dense_128_nl_layer, AI_STATIC,
  .tensors = &dense_128_chain, 
)

/* Layer #7: "dense_128_nl" (Nonlinearity) */
  


AI_TENSOR_CHAIN_OBJ_DECLARE(
  dense_128_nl_chain, AI_STATIC_CONST, 
  AI_TENSOR_LIST_ENTRY(&dense_128_output),
  AI_TENSOR_LIST_ENTRY(&dense_128_nl_output),
  AI_TENSOR_LIST_EMPTY,
  AI_TENSOR_LIST_EMPTY
)

AI_LAYER_OBJ_DECLARE(
  dense_128_nl_layer, 3,
  SM_TYPE,
  sm, forward_sm,
  &AI_NET_OBJ_INSTANCE, &dense_128_nl_layer, AI_STATIC,
  .tensors = &dense_128_nl_chain, 
)


AI_NETWORK_OBJ_DECLARE(
  AI_NET_OBJ_INSTANCE,
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 38508, 1,
                     NULL),
  AI_BUFFER_OBJ_INIT(AI_BUFFER_FORMAT_U8,
                     1, 1, 284, 1,
                     NULL),
  &input_0_output, &dense_128_nl_output,
  &dense_125_layer, 0)


AI_DECLARE_STATIC
ai_bool estimator_configure_activations(
  ai_network* net_ctx, const ai_buffer* activation_buffer)
{
  AI_ASSERT(net_ctx &&  activation_buffer && activation_buffer->data)

  ai_ptr activations = AI_PTR(AI_PTR_ALIGN(activation_buffer->data, 4));
  AI_ASSERT( activations )
  AI_FLAG_SET(net_ctx->flags, AI_NETWORK_FLAG_OUT_COPY);

  {
    /* Updating activations (byte) offsets */
    input_0_output_array.data = NULL;
  input_0_output_array.data_start = NULL;
  dense_125_output_array.data = activations + 0;
  dense_125_output_array.data_start = activations + 0;
  dense_125_nl_output_array.data = activations + 0;
  dense_125_nl_output_array.data_start = activations + 0;
  dense_126_output_array.data = activations + 140;
  dense_126_output_array.data_start = activations + 140;
  dense_126_nl_output_array.data = activations + 140;
  dense_126_nl_output_array.data_start = activations + 140;
  dense_127_output_array.data = activations + 0;
  dense_127_output_array.data_start = activations + 0;
  dense_127_nl_output_array.data = activations + 0;
  dense_127_nl_output_array.data_start = activations + 0;
  dense_128_output_array.data = activations + 140;
  dense_128_output_array.data_start = activations + 140;
  dense_128_nl_output_array.data = activations + 140;
  dense_128_nl_output_array.data_start = activations + 140;
  
  }
  return true;
}

AI_DECLARE_STATIC
ai_bool estimator_configure_weights(
  ai_network* net_ctx, const ai_buffer* weights_buffer)
{
  AI_ASSERT(net_ctx &&  weights_buffer && weights_buffer->data)

  ai_ptr weights = AI_PTR(weights_buffer->data);
  AI_ASSERT( weights )

  {
    /* Updating weights (byte) offsets */
    dense_125_weights_array.format |= AI_FMT_FLAG_CONST;
  dense_125_weights_array.data = weights + 0;
  dense_125_weights_array.data_start = weights + 0;
  dense_125_bias_array.format |= AI_FMT_FLAG_CONST;
  dense_125_bias_array.data = weights + 28000;
  dense_125_bias_array.data_start = weights + 28000;
  dense_126_weights_array.format |= AI_FMT_FLAG_CONST;
  dense_126_weights_array.data = weights + 28140;
  dense_126_weights_array.data_start = weights + 28140;
  dense_126_bias_array.format |= AI_FMT_FLAG_CONST;
  dense_126_bias_array.data = weights + 33040;
  dense_126_bias_array.data_start = weights + 33040;
  dense_127_weights_array.format |= AI_FMT_FLAG_CONST;
  dense_127_weights_array.data = weights + 33180;
  dense_127_weights_array.data_start = weights + 33180;
  dense_127_bias_array.format |= AI_FMT_FLAG_CONST;
  dense_127_bias_array.data = weights + 38080;
  dense_127_bias_array.data_start = weights + 38080;
  dense_128_weights_array.format |= AI_FMT_FLAG_CONST;
  dense_128_weights_array.data = weights + 38220;
  dense_128_weights_array.data_start = weights + 38220;
  dense_128_bias_array.format |= AI_FMT_FLAG_CONST;
  dense_128_bias_array.data = weights + 38500;
  dense_128_bias_array.data_start = weights + 38500;
  
  }

  return true;
}

/**  PUBLIC APIs SECTION  *****************************************************/

AI_API_ENTRY
ai_bool ai_estimator_get_info(
  ai_handle network, ai_network_report* report)
{
  ai_network* net_ctx = AI_NETWORK_ACQUIRE_CTX(network);

  if ( report && net_ctx )
  {
    ai_network_report r = {
      .model_name        = AI_ESTIMATOR_MODEL_NAME,
      .model_signature   = AI_ESTIMATOR_MODEL_SIGNATURE,
      .model_datetime    = AI_TOOLS_DATE_TIME,
      
      .compile_datetime  = AI_TOOLS_COMPILE_TIME,
      
      .runtime_revision  = ai_platform_runtime_get_revision(),
      .runtime_version   = ai_platform_runtime_get_version(),

      .tool_revision     = AI_TOOLS_REVISION_ID,
      .tool_version      = {AI_TOOLS_VERSION_MAJOR, AI_TOOLS_VERSION_MINOR,
                            AI_TOOLS_VERSION_MICRO, 0x0},
      .tool_api_version  = {AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR,
                            AI_TOOLS_API_VERSION_MICRO, 0x0},

      .api_version            = ai_platform_api_get_version(),
      .interface_api_version  = ai_platform_interface_api_get_version(),
      
      .n_macc            = 10600,
      .n_inputs          = AI_ESTIMATOR_IN_NUM,
      .inputs            = AI_BUFFER_OBJ_INIT(
                              AI_BUFFER_FORMAT_FLOAT,
                              1,
                              1,
                              200,
                              1, NULL),
      .n_outputs         = AI_ESTIMATOR_OUT_NUM,
      .outputs           = AI_BUFFER_OBJ_INIT(
                              AI_BUFFER_FORMAT_FLOAT,
                              1,
                              1,
                              2,
                              1, NULL),
      .activations       = net_ctx->activations,
      .weights           = net_ctx->params,
      .n_nodes           = 0,
      .signature         = net_ctx->signature,
    };

    AI_FOR_EACH_NODE_DO(node, net_ctx->input_node)
    {
      r.n_nodes++;
    }

    *report = r;

    return ( r.n_nodes>0 ) ? true : false;
  }
  
  return false;
}

AI_API_ENTRY
ai_error ai_estimator_get_error(ai_handle network)
{
  return ai_platform_network_get_error(network);
}

AI_API_ENTRY
ai_error ai_estimator_create(
  ai_handle* network, const ai_buffer* network_config)
{
  return ai_platform_network_create(
    network, network_config, 
    &AI_NET_OBJ_INSTANCE,
    AI_TOOLS_API_VERSION_MAJOR, AI_TOOLS_API_VERSION_MINOR, AI_TOOLS_API_VERSION_MICRO);
}

AI_API_ENTRY
ai_handle ai_estimator_destroy(ai_handle network)
{
  return ai_platform_network_destroy(network);
}

AI_API_ENTRY
ai_bool ai_estimator_init(
  ai_handle network, const ai_network_params* params)
{
  ai_network* net_ctx = ai_platform_network_init(network, params);
  if ( !net_ctx ) return false;

  ai_bool ok = true;
  ok &= estimator_configure_weights(net_ctx, &params->params);
  ok &= estimator_configure_activations(net_ctx, &params->activations);
  
  return ok;
}


AI_API_ENTRY
ai_i32 ai_estimator_run(
  ai_handle network, const ai_buffer* input, ai_buffer* output)
{
  return ai_platform_network_process(network, input, output);
}

AI_API_ENTRY
ai_i32 ai_estimator_forward(ai_handle network, const ai_buffer* input)
{
  return ai_platform_network_process(network, input, NULL);
}

#undef AI_ESTIMATOR_MODEL_SIGNATURE
#undef AI_NET_OBJ_INSTANCE
#undef AI_TOOLS_VERSION_MAJOR
#undef AI_TOOLS_VERSION_MINOR
#undef AI_TOOLS_VERSION_MICRO
#undef AI_TOOLS_API_VERSION_MAJOR
#undef AI_TOOLS_API_VERSION_MINOR
#undef AI_TOOLS_API_VERSION_MICRO
#undef AI_TOOLS_DATE_TIME
#undef AI_TOOLS_COMPILE_TIME

