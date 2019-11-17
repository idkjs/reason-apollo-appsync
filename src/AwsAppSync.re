module AuthLink = {
  /* https://github.com/awslabs/aws-mobile-appsync-sdk-js/blob/master/packages/aws-appsync-auth-link/src/index.ts */
  [@bs.deriving abstract]
  type authLinkOptions = {
    [@bs.as "type"]
    type_: string,
    apiKey: string,
  };
  type authLink;
  // define a translator function for the subscriptionLink type
  [@bs.obj]
  external authLink:
    (~url: string, ~region: string, ~auth: authLinkOptions, unit) => authLink =
    "";
  [@bs.module "aws-appsync-auth-link"] [@bs.new]
  external make: authLink => ReasonApolloTypes.apolloLink = "createAuthLink";

  external toApolloLink: 'a => ReasonApolloTypes.apolloLink = "%identity";
};

module SubscriptionLink = {
  type subscriptionLink; // create abstract subscriptionLink type

  [@bs.obj] // define a translator function for the subscriptionLink type
  external subscriptionLink:
    (~url: string, ~httpLink: ReasonApolloTypes.apolloLink, unit) =>
    subscriptionLink =
    ""; // returns a subscriptionLink;

  [@bs.module "aws-appsync-subscription-link"] [@bs.new]
  external make: subscriptionLink => unit = "createSubscriptionHandshakeLink";
};