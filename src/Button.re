[@react.component]
let make = (~text, ~cb) => {
  <button onClick={e => cb(e)}> {ReasonReact.string(text)} </button>;
};
