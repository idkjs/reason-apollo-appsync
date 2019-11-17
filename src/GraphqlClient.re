let fragmentsData = [%bs.raw {|require('../fragmentTypes.json')|}];
open Config;
/* Create an HTTP Link */
let httpLink = ApolloLinks.createHttpLink(~uri=config.graphqlEndpoint, ());
let auth =
  AwsAppSync.AuthLink.authLinkOptions(
    ~type_=config.authenticationType,
    ~apiKey=config.apiKey,
  );
let authLink =
  AwsAppSync.AuthLink.(
    make(
      authLink(~url=config.graphqlEndpoint, ~region=config.region, ~auth, ()),
    )
  );

let subcriptionLinkOptions =
  AwsAppSync.SubscriptionLink.subscriptionLink(
    ~url=config.graphqlEndpoint,
    ~httpLink,
    (),
  );
let subcriptionLink =
  AwsAppSync.SubscriptionLink.make(subcriptionLinkOptions);

let link = ApolloLinks.from([|authLink, httpLink|]);

let fragmentMatcher =
  ApolloInMemoryCache.createIntrospectionFragmentMatcher(~data=fragmentsData);

/* Create an InMemoryCache */
let inMemoryCache =
  ApolloInMemoryCache.createInMemoryCache(~fragmentMatcher, ());

let client = ReasonApollo.createApolloClient(~link, ~cache=inMemoryCache, ());