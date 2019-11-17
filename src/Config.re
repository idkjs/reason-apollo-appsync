
type t = {
  aws_project_region: string,
  identityPoolId: string,
  aws_cognito_region: string,
  userPoolsId: string,
  userPoolsWebClientId: string,
  graphqlEndpoint: string,
  region: string,
  authenticationType: string,
  apiKey: string,
};

[@bs.deriving abstract]
type awsExportsDecoder = {
  aws_project_region: string,
  aws_cognito_identity_pool_id: string,
  aws_cognito_region: string,
  aws_user_pools_id: string,
  aws_user_pools_web_client_id: string,
  aws_appsync_graphqlEndpoint: string,
  aws_appsync_region: string,
  aws_appsync_authenticationType: string,
  aws_appsync_apiKey: string,
};
let decode: awsExportsDecoder => t =
  data => {
    aws_project_region: aws_project_regionGet(data),
    identityPoolId: aws_cognito_identity_pool_idGet(data),
    aws_cognito_region: aws_cognito_regionGet(data),
    userPoolsId: aws_user_pools_idGet(data),
    userPoolsWebClientId: aws_user_pools_web_client_idGet(data),
    graphqlEndpoint: aws_appsync_graphqlEndpointGet(data),
    region: aws_appsync_regionGet(data),
    authenticationType: aws_appsync_authenticationTypeGet(data),
    apiKey: aws_appsync_apiKeyGet(data),
  };

[@bs.module "./aws-exports.js"] external awsConfig: awsExportsDecoder = "default";
let config = decode(awsConfig)